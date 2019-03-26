#include <cmath>
#include <algorithm>

#include <spdlog/spdlog.h>

#include "raytracer.hh"

#include "ambient-light.hh"
#include "chrono.hh"
#include "directional-light.hh"
#include "math.hh"
#include "object.hh"
#include "point-light.hh"
#include "polygon.hh"
#include "ray.hh"
#include "rgb.hh"
#include "vector3.hh"

namespace raytracer
{
    #define epsilon 0.0000001f
    #define MAX_DEPTH 4
    #define BIAS 0.0001f // to avoid self intersection

    image::RGBN ray_cast(const scene::Scene& scene, const Rayf& ray, const uint8_t& depth);

    struct Intersection
    {
        bool intersected = false;
        float nearest_t = -1;
        float nearest_u_bary;
        float nearest_v_bary;
        const scene::Polygon *nearest_polygon;
        float t;
        float u_bary;
        float v_bary;
    };

    bool moller_trumbore(const Vector3f& a_v, const Vector3f& b_v, const Vector3f& c_v,
                         const Rayf& ray, Intersection& isec)
    {
        Vector3f ab_v = b_v - a_v;
        Vector3f ac_v = c_v - a_v;
        Vector3f p_v = ray.dir ^ ac_v;
        const float det = ab_v * p_v;

        if (std::abs(det) < epsilon) // if ray and surface are parallel
            return false;

        float inv_det = 1.0 / det;
        Vector3f t_v = ray.o - a_v;
        isec.u_bary = t_v * p_v * inv_det;
        if (isec.u_bary < 0.0 || isec.u_bary > 1.0)
            return false;

        Vector3f q_v = t_v ^ ab_v;
        isec.v_bary = ray.dir * q_v * inv_det;
        if (isec.v_bary < 0.0 || isec.u_bary + isec.v_bary > 1.0)
            return false;

        isec.t = ac_v * q_v * inv_det;
        return true;
    }

    void intersect(const scene::Scene& scene, const Rayf& ray, Intersection& isec)
    {
        for (const auto& object : scene)
        {
            // FIXME: check bounding volume

            for (const auto& polygon : object.get_mesh())
            {
                // Compute triangle vertexes position in scene
                const Vector3f a_v = polygon[0].first + object.get_position();
                const Vector3f b_v = polygon[1].first + object.get_position();
                const Vector3f c_v = polygon[2].first + object.get_position();

                if (moller_trumbore(a_v, b_v, c_v, ray, isec)
                    && isec.t >= 0
                    && (isec.nearest_t == -1 || isec.t < isec.nearest_t))
                {
                    // save values of intersection as the nearest
                    isec.intersected = true;
                    isec.nearest_t = isec.t;
                    isec.nearest_u_bary = isec.u_bary;
                    isec.nearest_v_bary = isec.v_bary;
                    isec.nearest_polygon = &polygon;
                }
            }
        }
    }

    Vector3f interpolate_normals(const scene::Polygon& polygon,
                                  const float& u_bary, const float& v_bary)
    {
        const auto& n0 = polygon[0].second;
        const auto& n1 = polygon[1].second;
        const auto& n2 = polygon[2].second;

        return n0 * (1.f - u_bary - v_bary) + n1 * u_bary + n2 * v_bary;
    }

    image::RGBN compute_lights(const scene::Scene& scene, const Intersection& isec,
                               const Vector3f& P_v, const Vector3f& normal)
    {
        image::RGBN color = image::RGBN(0, 0, 0);

        const auto& material = isec.nearest_polygon->get_material();

        Vector3f L_v;
        float intensity;

        // foreach light
        for (auto it = scene.lights().begin(); it != scene.lights().end(); ++it)
        {
            Intersection shadow_isec;
            auto& light = *(*it);
            if (const auto *ambient_light = dynamic_cast<scene::AmbientLight*>(&light))
            {
                color += ambient_light->color * material.ambient * ambient_light->intensity;
                continue;
            }
            if (const auto *dir_light = dynamic_cast<scene::DirectionalLight*>(&light))
            {
                L_v = Vector3f(-dir_light->direction.x,
                               -dir_light->direction.y,
                               -dir_light->direction.z);
                L_v.normalize();
                intensity = dir_light->intensity;
            }
            else if (const auto *point_light = dynamic_cast<scene::PointLight*>(&light))
            {
                L_v = point_light->position - P_v; // direction of light, but reversed
                float r2 = L_v.norm();
                shadow_isec.nearest_t = std::sqrt(r2); // we search obstacles between P and light
                L_v.normalize();
                // square falloff
                intensity = point_light->intensity / (4 * M_PI * r2);
            }

            // shadow test
            const Ray light_ray = Ray(P_v + normal * BIAS, L_v);
            intersect(scene, light_ray, shadow_isec);
            // FIXME: could be optimized to not test all the objects after the first intersection
            if (!shadow_isec.intersected)
            {
                float cos_theta = normal * L_v;
                float coef = intensity * cos_theta;
                coef = clamp(coef, 0.f, 1.f);
                color += material.diffuse * light.color * coef;
            }
        }
        return color;
    }


    Vector3f reflect_dir(const Rayf& ray, const Vector3f& normal)
    {
        return ray.dir - (normal * (ray.dir * normal)) * 2;
    }

    Vector3f refract_dir(const Rayf& ray, const Vector3f& normal, float ior)
    {
        float cos_incident = clamp(ray.dir * normal, -1.f, 1.f);
        float eta1 = 1; // FIXME
        float eta2 = ior;
        Vector3f normal_copy = normal;
        if (cos_incident < 0) // if we're entering the material (from outside to inside)
            cos_incident = -cos_incident;
        else
        {
            std::swap(eta1, eta2);
            normal_copy = Vector3f(-normal.x, -normal.y, -normal.z);
        }
        float eta = eta1 / eta2;
        float k = 1 - eta * eta * (1 - cos_incident * cos_incident);
        if (k < 0)
            return Vector3f(0, 0, 0);
        else
            return ray.dir * eta + normal_copy * (eta * cos_incident - std::sqrt(k));

    }

    float fresnel(const Rayf& ray, const Vector3f& normal, float ior)
    {
        float cos_incident = clamp(ray.dir *  normal, -1.f, 1.f);
        float eta1 = 1; // FIXME
        float eta2 = ior;
        if (cos_incident > 0) // if we're leaving the material (from inside to outside)
            std::swap(eta1, eta2);
        float sin_transmit = eta1 / eta2 * std::sqrt(std::max(0.f, 1 - cos_incident * cos_incident));
        if (sin_transmit >= 1) // total internal reflection
            return 1;

        float cos_transmit = std::sqrt(std::max(0.f, 1 - sin_transmit * sin_transmit));
        cos_incident = std::abs(cos_incident);
        float Rs = ((eta2 * cos_incident) - (eta1 * cos_transmit)) / ((eta2 * cos_incident) + (eta1 * cos_transmit));
        float Rp = ((eta1 * cos_transmit) - (eta2 * cos_transmit)) / ((eta1 * cos_incident) + (eta2 * cos_transmit));
        return (Rs * Rs + Rp * Rp) / 2;
    }

    image::RGBN compute_refract(const scene::Scene& scene, const Rayf& ray,
                                const Intersection& isec, const Vector3f& P_v,
                                const Vector3f& normal, const uint8_t& depth)
    {
        const auto& material = isec.nearest_polygon->get_material();
        (void)material;
        float ior = 1.3; //FIXME: should come from MTL
        float reflect_coef = fresnel(ray, normal, ior);
        bool from_outside = (ray.dir * normal) < 0;
        Vector3f biased_normal = normal * BIAS;

        //FIXME: debug purpose
        //reflect_coef = 0;

        image::RGBN refract_color = image::RGBN(0, 0, 0);
        if (reflect_coef < 1)
        {
            Rayf refract_ray;
            refract_ray.dir = (refract_dir(ray, normal, ior)).normalize();
            refract_ray.o = from_outside ? P_v - biased_normal : P_v + biased_normal;

            refract_color = ray_cast(scene, refract_ray, depth + 1);
        }

        Rayf reflect_ray;
        reflect_ray.dir = (reflect_dir(ray, normal)).normalize();
        reflect_ray.o = from_outside ? P_v + biased_normal : P_v - biased_normal;
        image::RGBN reflect_color = ray_cast(scene, reflect_ray, depth + 1);

        return reflect_color * reflect_coef + refract_color * (1.f - reflect_coef);
    }


    image::RGBN ray_cast(const scene::Scene& scene, const Rayf& ray, const uint8_t& depth)
    {
        if (depth > MAX_DEPTH)
            return image::RGBN(0, 0, 0);

        Intersection isec;

        // Test ray intersection
        intersect(scene, ray, isec);
        if (isec.intersected)
        {
            image::RGBN color = image::RGBN(0, 0, 0);
            const auto normal = interpolate_normals(*isec.nearest_polygon,
                                                    isec.nearest_u_bary,
                                                    isec.nearest_v_bary);

            const auto& material = isec.nearest_polygon->get_material();
            // intersection point
            Vector3f P_v = ray.o + (ray.dir * isec.nearest_t);

            // FIXME: use the illum parameter from MTL file
            if (material.transparency != 0)
                color += compute_lights(scene, isec, P_v, normal) * material.transparency;
            if (material.transparency != 1)
                color += compute_refract(scene, ray, isec, P_v, normal, depth) * (1 - material.transparency);
            // FIXME: allow reflection without transparency

            return color;
        }
        else
            return image::RGBN(0.f, 0.f, 0.f);
    }

    const image::ImageRGB& render(const scene::Scene& scene)
    {
        spdlog::info("Starting raytracing process");
        double elapsed = 0;

        const float img_width = scene.get_width();
        const float img_height = scene.get_height();

        // Create image buffer
        auto& img = *(new image::ImageRGB(img_height, img_width));

        const auto origin = scene.get_camera().position;
        const float z_min = scene.get_camera().z_min;

        const float img_ratio = img_width / img_height;
        const float coef_x = tanf(scene.get_camera().fov_x / 2.0 * M_PI / 180.0) * img_ratio;
        const float coef_y = tanf(scene.get_camera().fov_y / 2.0 * M_PI / 180.0);

        {
            Chrono<std::chrono::seconds> chrono(elapsed);

            // Draw Loop
            for (int y = 0; y < img_height; ++y)
            {
                for (int x = 0; x < img_width; ++x)
                {
                    // x and y are expressed in raster space
                    // Screen space coordinates are in range [-1, 1]
                    float screen_x = (2.0 * (x + 0.5) / img_width - 1.0) * coef_x;
                    float screen_y = (1.0 - 2.0 * (y + 0.5) / img_height) * coef_y;
                    Vector3f target_pos = Vector3f(screen_x, screen_y, origin.z + z_min);

                    // Compute ray to cast from camera
                    Ray ray = Ray(origin, (target_pos - origin).normalize());

                    auto pixel_pos = std::pair(y, x);
                    img[pixel_pos] = ray_cast(scene, ray, 1);
                }
            }
        }

        spdlog::info("Finished rendering in {0} s", elapsed);
        return img;
    }
}

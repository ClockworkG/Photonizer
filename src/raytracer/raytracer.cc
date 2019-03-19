#include <cmath>

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
#include "photon-map.hh"

namespace raytracer
{
    #define epsilon 0.0000001
    #define MAX_DEPTH 4

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

#if 0

    Vector3f interpolate_normals(const scene::Polygon& polygon,
                                  const float& u_bary, const float& v_bary)
    {
        const auto& n0 = polygon[0].second;
        const auto& n1 = polygon[1].second;
        const auto& n2 = polygon[2].second;

        return n0 * (1.0f - u_bary - v_bary) + n1 * u_bary + n2 * v_bary;
    }

    image::RGBN compute_lights(const scene::Scene& scene, const Intersection& isec,
                               const Vector3f& P_v, const Vector3f& normal)
    {
        image::RGBN color = image::RGBN(0, 0, 0);

        const auto& material = isec.nearest_polygon->get_material();
        // FIXME: should come from material
        float albedo = 0.18f / M_PI;

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
            const float bias = 0.0001f; // to avoid self intersection
            const Ray light_ray = Ray(P_v + normal * bias, L_v);
            intersect(scene, light_ray, shadow_isec);
            // FIXME: could be optimized to not test all the objects after the first intersection
            if (!shadow_isec.intersected)
            {
                float cos_theta = normal * L_v;
                float coef = intensity * cos_theta * albedo;
                coef = clamp(coef, 0.0f, 1.0f);
                color += material.diffuse * light.color * coef;
            }
        }
        return color;
    }


    image::RGBN compute_specular(const scene::Scene& scene, const Rayf& ray,
                                 const Intersection& isec, const Vector3f& P_v,
                                 const Vector3f& normal, const uint8_t& depth)
    {
        image::RGBN color = image::RGBN(0, 0, 0);

        const auto& material = isec.nearest_polygon->get_material();

        const Vector3f R_v = ray.dir - (normal * (ray.dir * normal)) * 2;
        float bias = 0.0001f; // to avoid self intersection
        Ray specular_ray = Ray(P_v + normal * bias, R_v);
        color += material.specular * ray_cast(scene, specular_ray, depth + 1);

        return color;
    }
#endif


    float ray_cast(const scene::Scene& scene, const Rayf& ray, const uint8_t& depth,
                   const photon::PhotonMap& ph_map)
    {
        if (depth > MAX_DEPTH)
            return 0.f;

        Intersection isec;

        // Test ray intersection
        intersect(scene, ray, isec);
        if (isec.intersected)
        {
#if 0
            image::RGBN color = image::RGBN(0, 0, 0);
            const auto normal = interpolate_normals(*isec.nearest_polygon,
                                                    isec.nearest_u_bary,
                                                    isec.nearest_v_bary);

            Vector3f P_v = ray.o + (ray.dir * isec.nearest_t);

            color += compute_lights(scene, isec, P_v, normal);
            color += compute_specular(scene, ray, isec, P_v, normal, depth);
#endif
            auto hit = ray.o + ray.dir * isec.t;
            auto heap = ph_map.get_tree().nearest(
                    photon::Photon{hit},
                    1000, 0.1);
            return heap.size();
        }
        else
            return 0;
    }

    const image::Heatmap<float>& render(const scene::Scene& scene,
                                  const photon::PhotonMap& ph_map)
    {
        spdlog::info("Starting raytracing process");
        double elapsed = 0;

        const float img_width = scene.get_width();
        const float img_height = scene.get_height();

        // Create image buffer
        auto& img = *(new image::Heatmap<float>(img_height, img_width));

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
                    Vector3f target_pos = Vector3f(screen_x, screen_y, z_min);

                    // Compute ray to cast from camera
                    Ray ray = Ray(origin, (target_pos - origin).normalize());

                    auto pixel_pos = std::pair(y, x);
                    img[pixel_pos] = ray_cast(scene, ray, 1, ph_map);
                }
            }
        }

        spdlog::info("Finished rendering in {0} s", elapsed);
        return img;
    }
}

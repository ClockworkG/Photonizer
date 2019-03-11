#include "raytracer.hh"

#include <cmath>

#include "math.hh"
#include "object.hh"
#include "vector3.hh"
#include "ray.hh"
#include "rgb.hh"

namespace raytracer
{
    #define epsilon 0.000001


    struct Intersection
    {
        bool intersected = false;
        float nearest_t;
        float nearest_u_bary;
        float nearest_v_bary;
        scene::Polygon nearest_polygon;
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
        float det = ab_v * p_v;

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

    void intersect(const scene::Scene& scene, const Rayf& ray,
                   Intersection& isec)
    {
        for (const auto& object : scene)
        {
            // FIXME: check bounding volume

            for (const auto& polygon : object.get_mesh())
            {
                // Compute triangle vertexes position in scene
                Vector3f a_v = polygon[0].first + object.get_position();
                Vector3f b_v = polygon[1].first + object.get_position();
                Vector3f c_v = polygon[2].first + object.get_position();

                if (moller_trumbore(a_v, b_v, c_v, ray, isec)
                    && isec.t >= 0
                    && (isec.nearest_t == -1 || isec.t < isec.nearest_t))
                {
                    // save values of intersection as the nearest
                    isec.intersected = true;
                    isec.nearest_t = isec.t;
                    isec.nearest_u_bary = isec.u_bary;
                    isec.nearest_v_bary = isec.v_bary;
                    isec.nearest_polygon = polygon;
                }
            }
        }
    }

    image::RGBN compute_directional_light(scene::DirectionalLight light)
    {
        Vector3f L = Vector3f(-light.dir.x, -light.dir.y, -light.dir.z);
        // FIXME: should come from light
        float intensity = 15;
    }

    image::RGBN compute_point_light(scene::PointLight light, Vector3f P,
                                    Intersection& shadow_isec)
    {
        Vector3f L = light.position - P; // direction of light, but reversed
        float r2 = L.norm();
        shadow_isec.nearest_t = std::sqrt(r2);
        L.normalize();
        // square falloff
        image::RGBN color = light.diffuse * (intensity / (4 * M_PI * r2));
    }

    image::RGBN ray_cast(const scene::Scene& scene, const Rayf& ray)
    {
        Intersection isec;

        // Test ray intersection
        intersect(scene, ray, isec);
        if (isec.intersected)
        {
            const auto& n0 = isec.nearest_polygon[0].second;
            const auto& n1 = isec.nearest_polygon[1].second;
            const auto& n2 = isec.nearest_polygon[2].second;

            auto normal = n0 * (1.0f - isec.nearest_u_bary - isec.nearest_v_bary)
                          + n1 * isec.nearest_u_bary
                          + n2 * isec.nearest_v_bary;

            // FIXME: should come from material
            const auto& material = isec.nearest_polygon.get_material();
            float albedo = 1.0f;//0.18f;

            Vector3f P = ray.o + (ray.dir * isec.nearest_t);

            // foreach light
            // switch case

            // shadow test
            float bias = 0.0001f;
            Ray light_ray = Ray(P + normal * bias, L);
            Intersection shadow_isec;
            intersect(scene, light_ray, shadow_isec);
            // FIXME: could be optimized to not test all the objects after the first intersection
            if (!shadow_isec.intersected)
            {
                float cos_theta = normal * L;
                float coef = intensity * cos_theta * (albedo / M_PI);
                coef = clamp(coef, 0.0f, 1.0f);
                return material.ambient + scene.lights().front()->color * coef;
            }
            else
                return material.ambient;
        }
        else
            return image::RGBN(0.0f, 0.0f, 0.0f);
    }

    const image::ImageRGB& render(const scene::Scene& scene)
    {
        const float img_width = scene.get_width();
        const float img_height = scene.get_height();

        // Create image buffer
        auto& img = *(new image::ImageRGB(img_height, img_width));

        const auto origin = scene.get_camera().position;
        const float z_min = scene.get_camera().z_min;

        const float img_ratio = img_width / img_height;
        const float coef_x = tanf(scene.get_camera().fov_x / 2.0 * M_PI / 180.0) * img_ratio;
        const float coef_y = tanf(scene.get_camera().fov_y / 2.0 * M_PI / 180.0);

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
                img[pixel_pos] = ray_cast(scene, ray);
            }
        }
        return img;
    }
}

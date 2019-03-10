#include "raytracer.hh"

#include <cmath>
#include <iostream>

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
        float t;
        float u_bary;
        float v_bary;
        scene::Polygon polygon;
    };

    void moller_trumbore(const Vector3f& a_v, const Vector3f& b_v, const Vector3f& c_v,
                         const Rayf& ray, Intersection& isec)
    {
        Vector3f ab_v = b_v - a_v;
        Vector3f ac_v = c_v - a_v;
        Vector3f p_v = ray.dir ^ ac_v;
        float det = ab_v * p_v;

        if (std::abs(det) < epsilon) // if ray and surface are parallel
            return;

        float inv_det = 1.0 / det;
        Vector3f t_v = ray.o - a_v;
        isec.u_bary = t_v * p_v * inv_det;
        if (isec.u_bary < 0.0 || isec.u_bary > 1.0)
            return;

        Vector3f q_v = t_v ^ ab_v;
        isec.v_bary = ray.dir * q_v * inv_det;
        if (isec.v_bary < 0.0 || isec.u_bary + isec.v_bary > 1.0)
            return;

        isec.t = ac_v * q_v * inv_det;
        isec.intersected = true;
    }

    void intersect(const scene::Scene& scene, const Rayf& ray,
                   Intersection& nearest_isec)
    {
        // FIXME: isec.polygon could be a pointer or iterator to avoid initialization
        Intersection isec;

        for (const auto& object : scene)
        {
            // FIXME: check bounding volume

            for (const auto& polygon : object.get_mesh())
            {
                // Compute triangle vertexes position in scene
                Vector3f a_v = polygon[0].first + object.get_position();
                Vector3f b_v = polygon[1].first + object.get_position();
                Vector3f c_v = polygon[2].first + object.get_position();

                moller_trumbore(a_v, b_v, c_v, ray, isec);
                if (isec.intersected && isec.t >= 0
                    && (!nearest_isec.intersected || isec.t < nearest_isec.t))
                {
                    nearest_isec = isec;
                    nearest_isec.polygon = polygon;
                }
            }
        }
    }


    image::RGBN ray_cast(const scene::Scene& scene, const Rayf& ray)
    {
        Intersection nearest_isec;

        // Test ray intersection
        intersect(scene, ray, nearest_isec);
        if (nearest_isec.intersected)
        {
            //const auto& material = intersect_polygon.get_material();
            const auto& n0 = nearest_isec.polygon[0].second;
            const auto& n1 = nearest_isec.polygon[1].second;
            const auto& n2 = nearest_isec.polygon[2].second;

            auto normal = n0 * (1.0f - nearest_isec.u_bary - nearest_isec.v_bary)
                          + n1 * nearest_isec.u_bary
                          + n2 * nearest_isec.v_bary;

            // FIXME: should come from material
            float albedo = 0.18f;
            // FIXME: should come from light
            float intensity = 15;

            Vector3f P = ray.o + (ray.dir * nearest_isec.t);
            std::cerr << "P = " << P << std::endl;
            Vector3f L = P - scene.lights().front()->position;
            //Vector3f L = Vector3f(0, 0, 0) - scene.lights().front()->position;
            std::cerr << "L = " << L << std::endl;
            L.normalize();
            std::cerr << "Ln = " << L << std::endl;

            float cos_theta = normal * L;
            std::cerr << "cos theta = " << cos_theta << std::endl;
            float coef =  intensity * cos_theta * (albedo / M_PI);
            std::cerr << "coef = " << coef << std::endl;
            if (coef < 0)
                coef = 0;
            if (coef > 1)
                coef = 1;
            image::RGBN color = scene.lights().front()->color * coef;
            std::cerr << "color = " << color << std::endl;
            return color;
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
                //Ray ray = Ray(origin, (target_pos - origin).normalize());
                // FIXME: why not use origin in ray direction ?
                Ray ray = Ray(origin, target_pos.normalize());

                auto pixel_pos = std::pair(x, y);
                img[pixel_pos] = ray_cast(scene, ray);
            }
        }
        return img;
    }
}

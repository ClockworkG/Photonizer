#include "raytracer.hh"

#include <cmath>

#include "object.hh"
#include "vector3.hh"
#include "ray.hh"
#include "color.hh"
#include "rgb.hh"

namespace raytracer
{
    #define epsilon 0.000001

    bool moller_trumbore(const Vector3f& a_v, const Vector3f& b_v, const Vector3f& c_v,
                         const Rayf& ray, float& t)
    {
        Vector3f ab_v = b_v - a_v;
        Vector3f ac_v = c_v - a_v;
        Vector3f p_v = ray.dir ^ ac_v;
        float det = ab_v * p_v;

        if (std::abs(det) < epsilon)
            return false;

        float inv_det = 1.0 / det;
        Vector3f t_v = ray.o - a_v;
        float u_bary = t_v * p_v * inv_det;
        if (u_bary < 0.0 || u_bary > 1.0)
            return false;

        Vector3f q_v = t_v ^ ab_v;
        float v_bary = ray.dir * q_v * inv_det;
        if (v_bary < 0.0 || u_bary + v_bary > 1.0)
            return false;

        t = ac_v * q_v * inv_det;

        return true;
    }

    bool intersect(const scene::Scene& scene, const Rayf& ray)
    {
        float t;
        for (const auto& object : scene)
        {
            // FIXME: check box intersection

            for (const auto& polygon : object.get_mesh())
            {
                // Compute triangle vertexes position in scene
                Vector3f a_v = polygon[0].first + object.get_position();
                Vector3f b_v = polygon[1].first + object.get_position();
                Vector3f c_v = polygon[2].first + object.get_position();

                if (moller_trumbore(a_v, b_v, c_v, ray, t))
                    return true;
            }
        }
        return false;
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
                // FIXME: why -1 on z ?
                Vector3f target_pos = Vector3f(screen_x, screen_y, z_min);


                // Compute ray to cast from camera
                //Ray ray = Ray(origin, (target_pos - origin).normalize());
                // FIXME: why not use origin in ray direction ?
                Ray ray = Ray(origin, target_pos.normalize());

                auto pixel_pos = std::pair(x, y);
                // Test ray intersection
                if (intersect(scene, ray))
                    img[pixel_pos] = image::RGBN(1.0f, 1.0f, 1.0f); //FIXME
                else
                    img[pixel_pos] = image::RGBN(0.0f, 0.0f, 0.0f);
            }
        }
        return img;
    }
}

#include "raytracer.hh"

#include <cmath>

#include "object.hh"
#include "vector3.hh"
#include "ray.hh"
#include "color.hh"

namespace raytracer
{
    #define epsilon 0.0001

    bool moller_trumbore(scene::Mesh::polygon_t polygon, Rayf ray, float &t)
    {
        Vector3f ab_v = polygon[1].first - polygon[0].first;
        Vector3f ac_v = polygon[2].first - polygon[0].first;
        Vector3f p_vec = ray.dir ^ ac_v;
        float det = ab_v * p_vec;

        if (std::abs(det) < epsilon)
            return false;

        float inv_det = 1 / det;
        Vector3f t_vec = ray.o - polygon[0].first;
        float bary_u = t_vec * p_vec * inv_det;
        if (bary_u < 0 || bary_u > 1)
            return false;

        Vector3f q_vec = t_vec * ab_v;
        float bary_v = ray.dir * q_vec * inv_det;
        if (bary_v < 0 || bary_u + bary_v > 1)
            return false;

        t = ac_v * q_vec * inv_det;

        return true;
    }

    bool intersect(scene::Scene scene, Rayf ray)
    {
        float t = 0;
        for (auto object : scene)
        {
            // FIXME: check box intersection

            for (auto polygon : object.get_mesh())
            {
                if (moller_trumbore(polygon, ray, t))
                    return true;
            }
        }
        return false;
    }

    const image::ImageRGB& render(scene::Scene scene)
    {
        auto origin = scene.get_camera().position;
        auto up_uv = scene.get_camera().up;
        auto forward_uv = scene.get_camera().forward;

        float z_min = scene.get_camera().z_min;

        float width = scene.get_width();
        float height = scene.get_height();

        // Create image buffer
        auto& img = *(new image::ImageRGB(height, width));

        // Compute right unit vector
        Vector3f right_uv = up_uv ^ forward_uv;
        // Compute screen center
        Vector3f screen_center = origin + forward_uv * z_min;
        // Compute screen top left corner
        Vector3f screen_top_left = screen_center + up_uv * (height / 2) - right_uv * (width / 2);

        // Draw Loop
        for (int i = 0; i < height; ++i)
        {
            for (int j = 0; j < width; ++j)
            {
                // Compute pixel position on the view plane
                Vector3f target_pos = Vector3f(screen_top_left.x + i,
                                              screen_top_left.y + j,
                                              screen_top_left.z);


                // Compute ray to cast from camera
                Ray ray = Ray(origin, (target_pos - origin).normalize());

                auto pixel_pos = std::pair(i, j);
                // Test ray intersection
                if (intersect(scene, ray))
                    img[pixel_pos] = Color(1.0f, 1.0f, 1.0f);
                else
                    img[pixel_pos] = Color(0.0f, 0.0f, 0.0f);
            }
        }
        return img;
    }
}

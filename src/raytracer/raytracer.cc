#include "raytracer.hh"

#include <cmath>

#include "object.hh"
#include "vector3.hh"
#include "ray.hh"
#include "color.hh"

namespace raytracer
{
    #define epsilon 0.000001

    bool moller_trumbore(scene::Mesh::polygon_t polygon, Rayf ray, float &t)
    {
        Vector3f ab_v = polygon[1].first - polygon[0].first;
        Vector3f ac_v = polygon[2].first - polygon[0].first;
        Vector3f p_v = ray.dir ^ ac_v;
        float det = ab_v * p_v;

        if (std::abs(det) < epsilon)
            return false;

        float inv_det = 1.0 / det;
        Vector3f t_v = ray.o - polygon[0].first;
        float u_bary = t_v * p_v * inv_det;
        if (u_bary < 0.0 || u_bary > 1.0)
            return false;

        Vector3f q_v = t_v * ab_v;
        float v_bary = ray.dir * q_v * inv_det;
        if (v_bary < 0.0 || u_bary + v_bary > 1.0)
            return false;

        t = ac_v * q_v * inv_det;

        return true;
    }

    bool intersect(scene::Scene scene, Rayf ray)
    {
        float t;
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

        float img_width = scene.get_width();
        float img_height = scene.get_height();

        // Create image buffer
        auto& img = *(new image::ImageRGB(img_height, img_width));



        float screen_w = 0.35;
        float screen_h = 0.5;
        //z_min = 1;
        float x_step = screen_w / (float)img_width;
        float y_step = screen_h / (float)img_height;
        Vector3f right_uv = up_uv ^ forward_uv;
        Vector3f screen_center = origin + (forward_uv * z_min);
        Vector3f screen_top_left = screen_center + (up_uv * (screen_h / 2))
                                                 - (right_uv * (screen_w / 2));
/*
        // Compute right unit vector
        Vector3f right_uv = up_uv ^ forward_uv;
        // Compute screen center
        Vector3f screen_center = origin + forward_uv * z_min;
        // Compute screen top left corner
        Vector3f screen_top_left = screen_center + up_uv * (img_height / 2) - right_uv * (img_width / 2);

*/

        // Draw Loop
        for (int i = 0; i < img_height; ++i)
        {
            for (int j = 0; j < img_width; ++j)
            {
                /*
                // Compute pixel position on the view plane
                Vector3f target_pos = Vector3f(screen_top_left.x + i,
                                              screen_top_left.y + j,
                                              screen_top_left.z);
                */
                Vector3f target_pos = screen_top_left + (right_uv * x_step * i)
                                                      - (up_uv * y_step * j);


                // Compute ray to cast from camera
                Ray ray = Ray(origin, (target_pos - origin).normalize());

                auto pixel_pos = std::pair(i, j);
                // Test ray intersection
                if (intersect(scene, ray))
                    img[pixel_pos] = Color(255*1.0f, 255*1.0f, 255*1.0f); //FIXME
                else
                    img[pixel_pos] = Color(0.0f, 0.0f, 0.0f);
            }
        }
        return img;
    }
}

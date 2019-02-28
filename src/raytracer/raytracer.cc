#include "raytracer.hh"

#include "object.hh"
#include "vector3.hh"
#include "ray.hh"
#include "color.hh"

namespace raytracer
{
    bool intersect(scene::Scene scene, Rayf ray)
    {
        for (auto object : scene)
        {
            // FIXME: check box intersection

            for (auto polygon : object.get_mesh())
            {
                // triangle intersection
                if (polygon.size() == 3)
                {
                    // avoid warning
                    if (ray.o == ray.dir)
                        return false;
                    return true;
                }
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

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

            for (auto polygon : *(object.get_mesh()))
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
        auto origin = scene.get_camera().get_position();
        auto up = scene.get_camera().get_up();
        auto forward = scene.get_camera().get_forward();
        float z_min = 0; // FIXME: get from scene

        float width = scene.get_width();
        float height = scene.get_height();

        // Create image buffer
        auto& img = *(new image::ImageRGB(height, width));

        // Compute right unit vector
        Vector3f right = up ^ forward;
        // Compute screen center
        Vector3f screen_center = origin + forward * z_min;
        // Compute screen top left corner
        Vector3f screen_top_left = screen_center + up * (height / 2) - right * (width / 2);

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

#include "raytracer.hh"

#include "object.hh"
#include "vector3.hh"
#include "image-rgb.hh"
#include "color.hh"

namespace raytracer
{
    bool intersect(Scene scene, Ray ray)
    {
        for (auto object : scene)
        {
            // FIXME: check box intersection

            for (auto polygon : object.get_mesh())
            {
                // triangle intersection
                if (polygon.size() == 3)
                {
                    return true;
                }
            }
        }
        return false;
    }

    const ImageRGB& render(Scene scene)
    {
        using origin = scene.get_camera().get_position();
        using up = scene.get_camera().get_up();
        using forward = scene.get_camera().get_forward();

        using width = scene.get_width();
        using height = scene.get_height();

        // Create image buffer
        ImageRGB img(scene.get_height(height, width));

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
                Ray ray = Ray(origin, (pixel_pos - origin).normalize());

                point_t pixel_pos = std::pair<height_t, width_t>(i, j);
                // Test ray intersection
                if (intersect(scene, ray))
                    img[pixel_pos] = new Color(1.0f, 1.0f, 1.0f);
                else
                    img[pixel_pos] = new Color(0.0f, 0.0f, 0.0f);
            }
        }
    }
}

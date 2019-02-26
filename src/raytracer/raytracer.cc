#include "raytracer.hh"

#include "vector3.hh"
#include "image-rgb.hh"
#include "color.hh"

namespace raytracer
{
    const ImageRGB& render(Scene scene)
    {
        using origin = scene.get_camera().get_position();
        using up = scene.get_camera().get_up();
        using forward = scene.get_camera().get_forward();

        using width = scene.get_width();
        using height = scene.get_height();

        // Create image buffer
        ImageRGB buffer(scene.get_height(height, width));



        // Compute right unit vector
        Vector3f right = up ^ forward;
        // Compute screen center
        Vector3f screen_center = origin + forward * zmin;
        // Compute screen top left corner
        Vector3f screen_top_left = screen_center + up * (height / 2) - right * (width / 2);

        // FIXME
        // Compute incrementation step on X axis
        Vector3f x_step = 2.0f * right / width;
        // Compute incrementation step on y axis
        Vector3f x_step = 2.0f * up / height;

        // Draw Loop
        for (int i = 0; i < height; ++i)
        {
            for (int j = 0; j < width; ++j)
            {
                // FIXME
                // Compute pixel position on the view plane
                Vector3f pixel_pos = screen_top_left + i * y_step + j * x_step;


                // FIXME
                // Compute ray
                Ray ray = Ray(origin, /*direction*/);

                // Test ray intersection

                // If intersection, compute color
            }
        }
    }
}

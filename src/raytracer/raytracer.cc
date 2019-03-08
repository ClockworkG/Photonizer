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

    bool moller_trumbore(Vector3f a_v, Vector3f b_v, Vector3f c_v,
                         Rayf ray, float &t)
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

    bool triangle_intersect(scene::Mesh::polygon_t polygon, Rayf ray, float &t)
    {
        Vector3f ab_v = polygon[1].first - polygon[0].first;
        Vector3f ac_v = polygon[2].first - polygon[0].first;
        // compute plane's normal
        // no need to normalize
        Vector3f N = ab_v ^ ac_v; // N

        // Step 1: finding P

        // check if ray and plane are parallel ?
        float NdotRayDirection = N * ray.dir;
        if (std::abs(NdotRayDirection) < epsilon) // almost 0
            return false; // they are parallel so they don't intersect !

        // compute d parameter using equation 2
        float d = N * polygon[0].first;

        // compute t (equation 3)
        t = (N * ray.o + d) / NdotRayDirection;
        // check if the triangle is in behind the ray
        if (t < 0) return false; // the triangle is behind

        // compute the intersection point using equation 1
        Vector3f P = ray.o + (ray.dir * t);

        // Step 2: inside-outside test
        Vector3f C; // vector perpendicular to triangle's plane

        // edge 0
        Vector3f edge0 = polygon[1].first - polygon[0].first;
        Vector3f vp0 = P - polygon[0].first;
        C = edge0 * vp0;
        if (N * C < 0) return false; // P is on the right side

        // edge 1
        Vector3f edge1 = polygon[2].first - polygon[1].first;
        Vector3f vp1 = P - polygon[1].first;
        C = edge1 ^ vp1;
        if (N * C < 0) return false; // P is on the right side

        // edge 2
        Vector3f edge2 = polygon[0].first - polygon[2].first;
        Vector3f vp2 = P - polygon[2].first;
        C = edge2 ^ vp2;
        if (N * C < 0) return false; // P is on the right side;

        return true; // this ray hits the triangle 
    }

    bool intersect(scene::Scene scene, Rayf ray)
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

                //if (triangle_intersect(polygon, ray, t))
                if (moller_trumbore(a_v, b_v, c_v, ray, t))
                    return true;
            }
        }
        return false;
    }

    const image::ImageRGB& render(scene::Scene scene)
    {
        float img_width = scene.get_width();
        float img_height = scene.get_height();

        // Create image buffer
        auto& img = *(new image::ImageRGB(img_height, img_width));

        auto origin = scene.get_camera().position;
        float z_min = scene.get_camera().z_min;

        float img_ratio = img_width / img_height;
        float coef_x = tanf(scene.get_camera().fov_x / 2.0 * M_PI / 180.0) * img_ratio;
        float coef_y = tanf(scene.get_camera().fov_y / 2.0 * M_PI / 180.0);

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
                Vector3f target_pos = Vector3f(screen_x, screen_y, -z_min);


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

#pragma once

#include "libraytracer.hh"

#include <spdlog/spdlog.h>
#include <omp.h>

namespace raytracer
{
    template <typename Image, typename Tracer>
    Image render(scene::scene_ptr_t scene, photon::PhotonMap&& photon_map,
                 const RaytracerConfig& config)
    {
        static_assert(
                std::is_convertible_v<
                    typename Tracer::value_type,
                    typename Image::value_t
                >
        );
        spdlog::info("Starting raytracing process");
        spdlog::debug("Using {0} photons in radiance estimate", config.photon_gathering_count);
        spdlog::debug("Photon gathering with radius {0}", config.photon_gathering_radius);
        double elapsed = 0;

        const float img_width = scene->get_width();
        const float img_height = scene->get_height();

        auto sample_rate = config.sample_rate;

        // Create image buffer
        Image img(img_height, img_width);

        const auto origin = scene->get_camera().position;
        const float z_min = scene->get_camera().z_min;

        const float img_ratio = img_width / img_height;
        const float coef_x = tanf(scene->get_camera().fov_x / 2.f * M_PI / 180.f) * img_ratio;
        const float coef_y = tanf(scene->get_camera().fov_y / 2.f * M_PI / 180.f);

        const int nb_locks = img_height * img_width;
        auto locks = std::vector<omp_lock_t>(nb_locks);
        for (int i = 0; i < nb_locks; ++i)
            omp_init_lock(&(locks[i]));

        {
            Chrono<std::chrono::seconds> chrono(elapsed);

            Tracer ray_cast(scene, config, std::move(photon_map));

            // Draw Loop
            #pragma omp parallel for schedule(dynamic) \
                        shared(img, locks, ray_cast, sample_rate) default(none)
            for (int y = 0; y < sample_rate * img_height; ++y)
            {
                for (int x = 0; x < sample_rate * img_width; ++x)
                {
                    // x and y are expressed in raster space
                    // Screen space coordinates are in range [-1, 1]
                    float screen_x = (2.f * ((float)x + 0.5f) / (sample_rate * img_width) - 1.f) * coef_x;
                    float screen_y = (1.f - 2.f * ((float)y + 0.5f) / (sample_rate * img_height)) * coef_y;
                    Vector3f target_pos = Vector3f(screen_x, screen_y, origin.z + z_min);

                    // Compute ray to cast from camera
                    Ray ray = Ray(origin, (target_pos - origin).normalize());

                    int pixel_x = x / sample_rate;
                    int pixel_y = y / sample_rate;
                    int lock_pos = pixel_x * pixel_y;
                    auto pixel_pos = std::pair(pixel_y, pixel_x);

                    omp_set_lock(&(locks[lock_pos]));
                    img[pixel_pos] += ray_cast(ray) * (1.f / (float)(sample_rate * sample_rate));
                    omp_unset_lock(&(locks[lock_pos]));
                }
            }
        }

        for (int i = 0; i < nb_locks; i++)
            omp_destroy_lock(&(locks[i]));

        spdlog::info("Finished rendering in {0} s", elapsed);
        return img;

    }
} // namespace raytracer

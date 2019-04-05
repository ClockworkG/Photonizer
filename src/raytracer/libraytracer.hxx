#pragma once

#include "libraytracer.hh"

#include <spdlog/spdlog.h>
#include <future>

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

        // Create image buffer
        auto img = Image(img_height, img_width);

        const auto origin = scene->get_camera().position;
        const float z_min = scene->get_camera().z_min;

        const float img_ratio = img_width / img_height;
        const float coef_x = tanf(scene->get_camera().fov_x / 2.0 * M_PI / 180.0) * img_ratio;
        const float coef_y = tanf(scene->get_camera().fov_y / 2.0 * M_PI / 180.0);


        {
            Chrono<std::chrono::seconds> chrono(elapsed);

            Tracer ray_cast(scene, config, std::move(photon_map));

            // Multithreading
            size_t nb_pixels = img_width * img_height;
            std::vector<typename Tracer::value_type> img_flat(nb_pixels);
            size_t nb_cores = std::thread::hardware_concurrency();
            std::vector<std::future<void>> future_vector;

            for (size_t core_id = 0; core_id < nb_cores; ++core_id)
            {
                future_vector.emplace_back(std::async([=]()
                {
                    for (size_t index = core_id; index < nb_pixels; index += nb_cores)
                    {
                        size_t x = index % (int)img_width;
                        size_t y = index / (int)img_width;
                        /*
                        // Draw Loop
                        for (int y = 0; y < img_height; ++y)
                        {
                            for (int x = 0; x < img_width; ++x)
                            {
                            */
                                // x and y are expressed in raster space
                                // Screen space coordinates are in range [-1, 1]
                                float screen_x = (2.0 * (x + 0.5) / img_width - 1.0) * coef_x;
                                float screen_y = (1.0 - 2.0 * (y + 0.5) / img_height) * coef_y;
                                Vector3f target_pos = Vector3f(screen_x, screen_y, origin.z + z_min);

                                // Compute ray to cast from camera
                                Ray ray = Ray(origin, (target_pos - origin).normalize());

                                img_flat[index] = ray_cast(ray);
                            /*
                            }
                        }
                        */
                    }

                }));
            }
            for (size_t i = 0; i < nb_pixels; ++i)
            {
                size_t x = i % (int)img_width;
                size_t y = i / (int)img_width;

                auto pixel_pos = std::pair(y, x);
                img[pixel_pos] = img_flat[i];
            }
        }

        spdlog::info("Finished rendering in {0} s", elapsed);
        return img;

    }
} // namespace raytracer

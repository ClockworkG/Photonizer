#include "libphoton.hh"

#include <tuple>

#include <spdlog/spdlog.h>

#include "chrono.hh"
#include "point-light.hh"
#include "ray.hh"
#include "photon-tracer.hh"

namespace photon
{
    using photons_t = std::vector<Photon>;

    namespace
    {
        inline void emit_photons(const PhotonTracer& tracer,
                                 const scene::PointLight& light,
                                 const PhotonTracerConfig& config)
        {
            auto begin = tracer.size();
            std::size_t emitted = 0;

            while (emitted < config.max_photons)
            {
                Ray ray(light.position, tracer.randomize_direction());
                tracer(ray);
                emitted++;
            }

            for (auto i = begin; i < tracer.size(); i++)
                tracer[i].color *= (1 / static_cast<float>(emitted));
        }
    }

    PhotonMap build_photon_map(raytracer::scene_ptr_t scene,
                               const PhotonTracerConfig& config)
    {
        spdlog::info("Building photon map");

        PhotonTracer tracer(scene, config.max_bounces);
        double elapsed = 0;
        {
            spdlog::info("Tracing photons");
            spdlog::debug("Emitting {0} photons", config.max_photons);
            spdlog::debug("Maximum bounces: {0}", config.max_bounces);

            Chrono chrono(elapsed);
            for (const auto& light : scene->lights())
            {
                tracer.light = light;
                if (auto point_light =
                        std::dynamic_pointer_cast<const scene::PointLight>(light);
                        point_light != nullptr)
                {
                    emit_photons(tracer, *point_light, config);
                }
            }
        }

        spdlog::info("Photon tracing finished in {0} ms", elapsed);
        return PhotonMap(std::cbegin(tracer.get_photons()),
                         std::cend(tracer.get_photons()));
    }
} // namespace photon

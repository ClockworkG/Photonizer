#include "libphoton.hh"

#include "point-light.hh"

namespace photon
{
    using photons_t = std::vector<Photon>;

    namespace
    {
        inline void emit_photons(const scene::Scene&,
                                 const scene::PointLight&,
                                 const PhotonTracerConfig& config,
                                 photons_t& photons)
        {
            auto begin = photons.size();
            std::size_t emitted = 0;

            while (emitted < config.max_photons)
            {
                photons.emplace_back();
                emitted++;
            }

            for (auto i = begin; i < photons.size(); i++)
                photons[i].color *= (1 / static_cast<float>(emitted));
        }
    }

    PhotonMap build_photon_map(const scene::Scene& scene,
                               const PhotonTracerConfig& config)
    {
        photons_t photons{};

        for (const auto& light : scene.lights())
        {
            if (auto point_light =
                    std::dynamic_pointer_cast<const scene::PointLight>(light);
                point_light != nullptr)
            {
                emit_photons(scene, *point_light, config, photons);
            }
        }

        return PhotonMap(std::cbegin(photons), std::cend(photons));
    }
} // namespace photon

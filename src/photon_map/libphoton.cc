#include "libphoton.hh"

#include <random>
#include <tuple>

#include "point-light.hh"
#include "ray.hh"

#include "helpers.hh" // XXX: to remove

namespace photon
{
    using photons_t = std::vector<Photon>;

    namespace
    {
        inline Vector3f
        randomize_direction(std::mt19937& engine,
                            std::uniform_real_distribution<>& dist)
        {
            float x = 0;
            float y = 0;
            float z = 0;

            do {
                x = 2 * dist(engine) - 1;
                y = 2 * dist(engine) - 1;
                z = 2 * dist(engine) - 1;
            } while (x * x + y * y + z * z > 1);

            return Vector3f(x, y, z).normalize();
        }

        inline void emit_photons(const scene::Scene& scene,
                                 const scene::PointLight& light,
                                 const PhotonTracerConfig& config,
                                 photons_t& photons)
        {
            auto begin = photons.size();
            std::size_t emitted = 0;
            std::random_device rd{};
            std::mt19937 engine(rd());
            std::uniform_real_distribution<> dist(0.0f, 1.0f);

            while (emitted < config.max_photons)
            {
                auto direction = randomize_direction(engine, dist);
                Ray ray(light.position, direction);
                Intersection isec;

                intersect(scene, ray, isec);

                auto hit_point = light.position + direction * isec.nearest_t;
                auto ph = Photon(hit_point);
                std::tie(ph.phi, ph.theta) = polar_convert(direction);

                photons.push_back(std::move(ph));
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

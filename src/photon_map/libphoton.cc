#include "libphoton.hh"

#include <random>
#include <tuple>

#include <spdlog/spdlog.h>

#include "chrono.hh"
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

        [[maybe_unused]]
        inline std::pair<float, float>
        next_direction(std::mt19937& engine,
                       std::uniform_real_distribution<>& dist)
        {
            return std::make_pair(
                    2 * M_PI * dist(engine) * 256,
                    acos(std::sqrt(dist(engine))) * 256
            );
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
                auto [phi, theta] = polar_convert(direction);
                auto origin = light.position;
                std::size_t bounces = 0;

                while (bounces < config.max_bounces)
                {
                    Ray ray(origin, direction);
                    Intersection isec;

                    intersect(scene, ray, isec);
                    if (!isec.intersected)
                        break;

                    auto hit_point = origin + direction * isec.nearest_t;
                    auto ph = Photon(hit_point);
                    ph.color = light.color * isec.nearest_polygon->get_material().diffuse;
                    ph.phi = phi;
                    ph.theta = theta;

                    photons.push_back(std::move(ph));

                    if (true)
                    {
                        origin = hit_point;
                        // FIXME: Not the correct way to bounce a photon
                        // The direction should be restricted to the
                        // upper hemisphere.
                        direction = randomize_direction(engine, dist);
                        std::tie(phi, theta) = polar_convert(direction);

                        bounces++;
                    }
                }

                emitted++;
            }

            for (auto i = begin; i < photons.size(); i++)
                photons[i].color *= (1 / static_cast<float>(emitted));
        }
    }

    PhotonMap build_photon_map(const scene::Scene& scene,
                               const PhotonTracerConfig& config)
    {
        spdlog::info("Building photon map");
        photons_t photons{};

        double elapsed = 0;
        {
            spdlog::info("Tracing photons");
            spdlog::debug("Emitting {0} photons", config.max_photons);
            spdlog::debug("Maximum bounces: {0}", config.max_bounces);

            Chrono chrono(elapsed);
            for (const auto& light : scene.lights())
            {
                if (auto point_light =
                        std::dynamic_pointer_cast<const scene::PointLight>(light);
                        point_light != nullptr)
                {
                    emit_photons(scene, *point_light, config, photons);
                }
            }
        }

        spdlog::info("Photon tracing finished in {0} ms", elapsed);
        return PhotonMap(std::cbegin(photons), std::cend(photons));
    }
} // namespace photon

#pragma once

#include <memory>

#include "photon-map.hh"
#include "libscene.hh"

namespace photon
{
    struct PhotonTracerConfig
    {
        PhotonTracerConfig() = default;

        std::size_t max_photons = 10000;
        std::size_t max_bounces = 3;
    };

    [[nodiscard]]
    PhotonMap build_photon_map(const scene::Scene& scene,
                               const PhotonTracerConfig& config);
} // namespace photon

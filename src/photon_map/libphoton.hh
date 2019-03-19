#pragma once

#include <memory>

#include "photon-map.hh"
#include "libscene.hh"

namespace photon
{
    struct PhotonTracerConfig
    {
        std::size_t max_photons;
        std::size_t query_size;
        float       query_radius;
    };

    [[nodiscard]]
    PhotonMap build_photon_map(const scene::Scene& scene,
                               const PhotonTracerConfig& config);
} // namespace photon
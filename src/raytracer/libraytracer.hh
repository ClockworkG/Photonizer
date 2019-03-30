#pragma once

#include "scene.hh"
#include "photon-map.hh"
#include "ray-tracer.hh"
#include "chrono.hh"

namespace raytracer
{
    template <typename Image>
    Image render(scene::scene_ptr_t scene, photon::PhotonMap&& photon_map,
                 const RaytracerConfig& config);
} // namespace raytracer

#include "libraytracer.hxx"

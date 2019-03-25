#pragma once

#include "scene.hh"
#include "photon-map.hh"

namespace raytracer
{
    using scene_ptr_t = std::shared_ptr<const scene::Scene>;

    template <typename Image>
    Image render(scene_ptr_t scene, photon::PhotonMap&& photon_map);
} // namespace raytracer

#include "libraytracer.hxx"

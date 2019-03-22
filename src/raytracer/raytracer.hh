#pragma once

#include "scene.hh"
#include "image-rgb.hh"
#include "photon-map.hh"
#include "heatmap.hh"

namespace raytracer
{
    image::ImageRGB render(const scene::Scene& scene,
                           const photon::PhotonMap& ph_map);
}

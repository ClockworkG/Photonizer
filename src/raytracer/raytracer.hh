#pragma once

#include "scene.hh"
#include "image-rgb.hh"

namespace raytracer
{
    [[deprecated("Move to render defined in libraytracer.hh")]]
    const image::ImageRGB& render(const scene::Scene& scene);
}

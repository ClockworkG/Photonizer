#pragma once

#include "scene.hh"
#include "image-rgb.hh"

namespace raytracer
{
    const image::ImageRGB& render(scene::Scene scene);
}

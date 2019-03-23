#pragma once

#include "scene.hh"

namespace raytracer
{
    using scene_ptr_t = std::shared_ptr<const scene::Scene>;

    template <typename Image>
    Image render(scene_ptr_t scene);
} // namespace raytracer

#include "libraytracer.hxx"

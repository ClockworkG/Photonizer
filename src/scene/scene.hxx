#pragma once

#include "scene.hh"

namespace scene
{
    inline Scene::const_iterator Scene::begin() const
    {
        return std::cbegin(objects_);
    }

    inline Scene::const_iterator Scene::end() const
    {
        return std::cend(objects_);
    }

    inline const Camera& Scene::get_camera() const noexcept
    {
        return camera_;
    }
} // namespace scene

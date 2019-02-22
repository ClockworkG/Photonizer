#pragma once

#include "camera.hh"

namespace scene
{
    inline
    Camera::Camera(const Vector3f& pos, const Vector3f& fwd,
                   const Vector3f& up, float fov) noexcept
        : position_(pos)
        , forward_(fwd)
        , up_(up)
        , fov_(fov)
    {}

    inline Vector3f Camera::get_position() const noexcept
    {
        return position_;
    }

    inline Vector3f Camera::get_forward() const noexcept
    {
        return forward_;
    }

    inline Vector3f Camera::get_up() const noexcept
    {
        return up_;
    }

    inline float Camera::get_fov() const noexcept
    {
        return fov_;
    }
} // namespace scene

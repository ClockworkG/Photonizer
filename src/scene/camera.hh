#pragma once

#include "vector3.hh"

namespace scene
{
    class Camera
    {
    public:
        Camera() = default;
        Camera(const Vector3f& pos,
               const Vector3f& fwd,
               const Vector3f& up) noexcept;
        ~Camera() = default;
        Camera(const Camera&) = delete;
        Camera(Camera&&) = delete;
        Camera& operator=(const Camera&) = delete;
        Camera& operator=(Camera&&) = delete;

    private:
        Vector3f pos_;
        Vector3f fwd_;
        Vector3f up_;
    };

    inline
    Camera::Camera(const Vector3f& pos,
                   const Vector3f& fwd,
                   const Vector3f& up) noexcept
        : pos_(pos)
        , fwd_(fwd)
        , up_(up)
    {}
} // namespace scene

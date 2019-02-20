#pragma once

#include "vector3.hh"

namespace scene
{
    class Camera
    {
    public:
        Camera() = default;
        Camera(Vector3f pos, Vector3f fwd, Vector3f up) noexcept;
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
} // namespace scene

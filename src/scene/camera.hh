#pragma once

#include "vector3.hh"

namespace scene
{
    /// Camera from which the scene is viewed.
    struct Camera
    {
    public:
        /** \name Ctors & dtor.
         * \{ */
        Camera() = default;
        ~Camera() = default;
        Camera(const Camera&) = default;
        Camera(Camera&&) = default;
        Camera& operator=(const Camera&) = default;
        Camera& operator=(Camera&&) = default;
        /** \} */

        /// Position of the camera.
        Vector3f position;
        /// Forward direction.
        Vector3f forward;
        /// Up directions.
        Vector3f up;
        /// Field of view (on X).
        float    fov_x;
        /// Field of view (on Y).
        float    fov_y;
        /// Image plane distance.
        float    z_min;
    };
} // namespace scene

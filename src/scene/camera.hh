#pragma once

#include "vector3.hh"

namespace scene
{
    /// Camera from which the scene is viewed.
    class Camera
    {
    public:
        /** \name Ctors and dtors.
         * \{ */
        Camera() = default;
        Camera(const Vector3f& pos, const Vector3f& fwd,
               const Vector3f& up, float fov) noexcept;
        ~Camera() = default;
        Camera(const Camera&) = default;
        Camera(Camera&&) = default;
        Camera& operator=(const Camera&) = default;
        Camera& operator=(Camera&&) = default;
        /** \} */

        /** \name Getters.
         * \{ */
        Vector3f get_position() const noexcept;
        Vector3f get_forward() const noexcept;
        Vector3f get_up() const noexcept;
        float    get_fov() const noexcept;
        /** \} */

    private:
        /// Position of the camera.
        Vector3f position_;
        /// Forward direction.
        Vector3f forward_;
        /// Up directions.
        Vector3f up_;
        /// Field of view.
        float    fov_;
    };
} // namespace scene

#include "camera.hxx"

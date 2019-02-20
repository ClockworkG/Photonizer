#include "camera.hh"

namespace scene
{
    Camera::Camera(Vector3f pos, Vector3f fwd, Vector3f up) noexcept
        : pos_(pos)
        , fwd_(fwd)
        , up_(up)
    {}
} // namespace scene

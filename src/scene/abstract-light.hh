#pragma once

#include "color.hh"
#include "vector3.hh"

namespace scene
{
    struct AbstractLight
    {
        /** \name Ctors & dtor.
         * \{ */
        AbstractLight() = default;
        AbstractLight(const Vector3f& position_init, const Color& color_init)
            noexcept;
        virtual ~AbstractLight() = default;
        AbstractLight(const AbstractLight&) = delete;
        AbstractLight(AbstractLight&&) = delete;
        AbstractLight& operator=(const AbstractLight&) = delete;
        AbstractLight& operator=(AbstractLight&&) = delete;
        /** \} */

        /// Position of the light.
        Vector3f position;
        /// Diffuse color.
        Color color;
    };

    inline AbstractLight::AbstractLight(const Vector3f& position_init,
                                        const Color& color_init) noexcept
        : position(position_init)
        , color(color_init)
    {}
} // namespace scene

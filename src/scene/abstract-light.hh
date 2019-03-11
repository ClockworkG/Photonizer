#pragma once

#include "rgb.hh"
#include "vector3.hh"

namespace scene
{
    struct AbstractLight
    {
        /** \name Ctors & dtor.
         * \{ */
        AbstractLight(const image::RGBN& color_init,
                      float intensity_init);
        virtual ~AbstractLight() = default;
        AbstractLight(const AbstractLight&) = delete;
        AbstractLight(AbstractLight&&) = delete;
        AbstractLight& operator=(const AbstractLight&) = delete;
        AbstractLight& operator=(AbstractLight&&) = delete;
        /** \} */

        /// Diffuse color.
        const image::RGBN color;
        /// Intensity.
        const float intensity;
    };

    inline
    AbstractLight::AbstractLight(const image::RGBN& color_init,
                  float intensity_init)
        : color(color_init)
        , intensity(intensity_init)
    {}
} // namespace scene

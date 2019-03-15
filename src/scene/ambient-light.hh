#pragma once

#include "abstract-light.hh"

namespace scene
{
    struct AmbientLight : public AbstractLight
    {
        /** \name Ctors & dtor.
         * \{ */
        AmbientLight(const image::RGBN& color_init,
                      float intensity_init);
        virtual ~AmbientLight() = default;
        AmbientLight(const AmbientLight&) = delete;
        AmbientLight(AmbientLight&&) = delete;
        AmbientLight& operator=(const AmbientLight&) = delete;
        AmbientLight& operator=(AmbientLight&&) = delete;
        /** \} */
    };

    inline
    AmbientLight::AmbientLight(const image::RGBN& color_init,
                               float intensity_init)
        : AbstractLight(color_init, intensity_init)
    {}
} // namespace scene

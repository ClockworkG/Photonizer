#pragma once

#include "abstract-light.hh"

namespace scene
{
    struct DirectionalLight : public AbstractLight
    {
        /** \name Ctors & dtor.
         * \{ */
        DirectionalLight(const image::RGBN& color_init, float intensity_init,
                   const Vector3f& position_init);
        virtual ~DirectionalLight() = default;
        DirectionalLight(const DirectionalLight&) = delete;
        DirectionalLight(DirectionalLight&&) = delete;
        DirectionalLight& operator=(const DirectionalLight&) = delete;
        DirectionalLight& operator=(DirectionalLight&&) = delete;
        /** \} */

        const Vector3f direction;
    };

    inline
    DirectionalLight::DirectionalLight(const image::RGBN& color_init,
                                       float intensity_init,
                                       const Vector3f& dir_init)
        : AbstractLight(color_init, intensity_init)
        , direction(dir_init)
    {}
} // namespace scene

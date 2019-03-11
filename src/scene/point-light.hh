#pragma once

#include "abstract-light.hh"

namespace scene
{
    struct PointLight : public AbstractLight
    {
        /** \name Ctors & dtor.
         * \{ */
        PointLight(const image::RGBN& color_init, float intensity_init,
                   const Vector3f& position_init);
        virtual ~PointLight() = default;
        PointLight(const PointLight&) = delete;
        PointLight(PointLight&&) = delete;
        PointLight& operator=(const PointLight&) = delete;
        PointLight& operator=(PointLight&&) = delete;
        /** \} */

        const Vector3f position;
    };

    inline
    PointLight::PointLight(const image::RGBN& color_init, float intensity_init,
                           const Vector3f& position_init)
        : AbstractLight(color_init, intensity_init)
        , position(position_init)
    {}
} // namespace scene

#pragma once

#include "abstract-light.hh"

namespace scene
{
    struct PointLight : public AbstractLight
    {
        /** \name Ctors & dtor.
         * \{ */
        PointLight() = default;
        PointLight(const Vector3f& position_init,
                   const image::RGBN& color_init) noexcept;
        virtual ~PointLight() = default;
        PointLight(const PointLight&) = delete;
        PointLight(PointLight&&) = delete;
        PointLight& operator=(const PointLight&) = delete;
        PointLight& operator=(PointLight&&) = delete;
        /** \} */
    };

    inline PointLight::PointLight(const Vector3f& position_init,
                                  const image::RGBN& color_init) noexcept
        : AbstractLight(position_init, color_init)
    {}
} // namespace scene

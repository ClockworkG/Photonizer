#pragma once

#include "abstract-light.hh"

namespace scene
{
    struct SquareLight : public AbstractLight
    {
        /** \name Ctors & dtor.
         * \{ */
        SquareLight(const image::RGBN& color_init,
                    float intensity_init,
                    const Vector3f& center_init,
                    float width_init, float height_init);
        virtual ~SquareLight() = default;
        SquareLight(const SquareLight&) = delete;
        SquareLight(SquareLight&&) = delete;
        SquareLight& operator=(const SquareLight&) = delete;
        SquareLight& operator=(SquareLight&&) = delete;
        /** \} */

        const Vector3f center;
        const float width;
        const float height;
    };

    inline
    SquareLight::SquareLight(const image::RGBN& color_init,
                             float intensity_init,
                             const Vector3f& center_init,
                             float width_init, float height_init)
        : AbstractLight(color_init, intensity_init)
        , center(center_init)
        , width(width_init)
        , height(height_init)
    {}
} // namespace scene

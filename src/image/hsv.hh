#pragma once

#include <array>

#include "rgb.hh"

namespace image
{
    class HSV
    {
    public:
        using hue_t = float;

        explicit constexpr HSV(hue_t h = 0, float s = 0, float v = 0) noexcept;
        HSV(const HSV&) noexcept = default;
        HSV(HSV&&) noexcept = default;
        HSV& operator=(const HSV&) noexcept = default;
        HSV& operator=(HSV&&) noexcept = default;

        explicit operator RGB() const noexcept;

        hue_t h() const noexcept;
        float s() const noexcept;
        float v() const noexcept;

        void set_h(hue_t h);
        void set_s(float s);
        void set_v(float h);

    private:
        hue_t h_ = 0;
        float s_ = 0;
        float v_ = 0;
    };
} // namespace image

#include "hsv.hxx"

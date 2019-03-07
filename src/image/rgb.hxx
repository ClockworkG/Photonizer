#pragma once

#include "rgb.hh"

namespace image
{
    inline
    constexpr RGB::RGB(uint8_t r_init, uint8_t g_init, uint8_t b_init)
    noexcept
        : r{r_init}
        , g{g_init}
        , b{b_init}
    {}

    inline
    RGBN::RGBN(float r_init, float g_init, float b_init)
        : r{r_init}
        , g{g_init}
        , b{b_init}
    {
        if (r < 0 || r > 1)
            throw std::domain_error{"Red component is not normalized."};
        else if (g < 0 || g > 1)
            throw std::domain_error{"Green component is not normalized."};
        else if (b < 0 || b > 1)
            throw std::domain_error{"Blue component is not normalized."};
    }

    inline
    RGB::operator RGBN() const noexcept
    {
        return RGBN
        (
            static_cast<float>(r) / 255.f,
            static_cast<float>(g) / 255.f,
            static_cast<float>(b) / 255.f
        );
    }

    inline
    RGBN::operator RGB() const noexcept
    {
        return RGB
        (
            r * 255,
            g * 255,
            b * 255
        );
    }

    inline
    RGBN& RGBN::operator+=(float value) noexcept
    {
        r += value;
        g += value;
        b += value;
        return *this;
    }
} // namespace image

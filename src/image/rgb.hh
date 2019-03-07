#pragma once

#include <array>

namespace image
{
    struct RGBN;

    struct RGB
    {
        constexpr RGB(uint8_t r_init = 0, uint8_t g_init = 0,
                      uint8_t b_init = 0) noexcept;
        ~RGB() = default;
        RGB(const RGB&) noexcept = default;
        RGB(RGB&&) noexcept = default;
        RGB& operator=(const RGB&) noexcept = default;
        RGB& operator=(RGB&&) noexcept = default;

        operator RGBN() const noexcept;

        uint8_t r;
        uint8_t g;
        uint8_t b;
    };

    struct RGBN
    {
        RGBN(float r_init = 0, float g_init = 0,
             float b_init = 0);
        ~RGBN() = default;
        RGBN(const RGBN&) noexcept = default;
        RGBN(RGBN&&) noexcept = default;
        RGBN& operator=(const RGBN&) noexcept = default;
        RGBN& operator=(RGBN&&) noexcept = default;

        operator RGB() const noexcept;

        RGBN& operator+=(float value) noexcept;

        float r;
        float g;
        float b;
    };

} // namespace image

#include "rgb.hxx"

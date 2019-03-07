#pragma once

#include "hsv.hh"

namespace image
{
    inline
    constexpr
    HSV::HSV(hue_t h, float s, float v) noexcept
        : h_{h}
        , s_{s}
        , v_{v}
    {}

    HSV::operator RGB() const noexcept
    {
        auto var_h = h_ * 6;
        if (var_h == 6)
            var_h = 0;

        auto var_i = static_cast<int>(var_h);
        auto var_1 = v_ * (1 - s_);
        auto var_2 = v_ * (1 - s_ * (var_h - var_i));
        auto var_3 = v_ * (1 - s_ * (1 - (var_h - var_i)));

        RGBN normalized{};
        switch (var_i)
        {
        case 0:
            normalized = RGBN{v_, var_3, var_1};
            break;
        case 1:
            normalized = RGBN{var_2, v_, var_1};
            break;
        case 2:
            normalized = RGBN{var_1, v_, var_3};
            break;
        case 3:
            normalized = RGBN{var_1, var_2, v_};
            break;
        case 4:
            normalized = RGBN{var_3, var_1, v_};
            break;
        default:
            normalized = RGBN{v_, var_1, var_2};
        };

        return normalized;
    }

    inline
    auto HSV::h() const noexcept -> hue_t
    {
        return h_;
    }

    inline
    auto HSV::s() const noexcept -> float
    {
        return s_;
    }

    inline
    auto HSV::v() const noexcept -> float
    {
        return v_;
    }

    void HSV::set_h(hue_t h)
    {
        if (h < 0 || h > 1)
            throw std::domain_error{"Hue must be between 0f and 1f."};
        h_ = h;
    }

    void HSV::set_s(float s)
    {
        if (s < 0 || s > 1)
            throw std::domain_error{"Saturation must be between 0f and 1f."};
        s_ = s;
    }

    void HSV::set_v(float v)
    {
        if (v < 0 || v > 1)
            throw std::domain_error{"Value must be between 0f and 1f."};
        v_ = v;
    }
} // namespace image

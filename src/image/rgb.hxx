#pragma once

#include "rgb.hh"

namespace image
{
    ///////////////////////////////////////////////////////////////////////////
    // RGB
    ///////////////////////////////////////////////////////////////////////////

    inline
    RGB::RGB(uint16_t r_init, uint16_t g_init, uint16_t b_init)
        : r{r_init}
        , g{g_init}
        , b{b_init}
    {
        if (r > 255)
            throw std::domain_error{"Red component is greater than 255."};
        else if (g > 255)
            throw std::domain_error{"Green component is greater than 255."};
        else if (b > 255)
            throw std::domain_error{"Blue component is greater than 255."};
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
    RGB& RGB::operator+=(const RGB& other) noexcept
    {
        r = clamp(r + other.r, 255);
        g = clamp(g + other.g, 255);
        b = clamp(b + other.b, 255);
        return *this;
    }

    inline
    RGB& RGB::operator-=(const RGB& other) noexcept
    {
        r = clamp(r - other.r, 0, 255);
        g = clamp(g - other.g, 0, 255);
        b = clamp(b - other.b, 0, 255);
        return *this;
    }

    inline
    RGB& RGB::operator*=(const RGB& other) noexcept
    {
        r = clamp(r * other.r, 255);
        g = clamp(g * other.g, 255);
        b = clamp(b * other.b, 255);
        return *this;
    }

    template <typename T>
    RGB& RGB::operator*=(T other) noexcept
    {
        static_assert(std::is_integral_v<T>);
        r = clamp(r * other, 255);
        g = clamp(g * other, 255);
        b = clamp(b * other, 255);
        return *this;
    }

    inline
    uint16_t& RGB::operator[](unsigned short index)
    {
        if (index == 0)
            return r;
        if (index == 1)
            return g;
        if (index == 2)
            return b;
        throw std::out_of_range{"Color index out of range."};
    }

    inline
    uint16_t RGB::operator[](unsigned short index) const
    {
        if (index == 0)
            return r;
        if (index == 1)
            return g;
        if (index == 2)
            return b;
        throw std::out_of_range{"Color index out of range."};
    }

    inline
    bool operator==(const RGB& lhs, const RGB& rhs) noexcept
    {
        return lhs.r && rhs.r && lhs.g == rhs.g && lhs.b == rhs.b;
    }

    inline
    bool operator!=(const RGB& lhs, const RGB& rhs) noexcept
    {
        return !(lhs == rhs);
    }

    inline
    RGB operator+(const RGB& lhs, const RGB& rhs) noexcept
    {
        RGB result{lhs};
        result += rhs;
        return result;
    }

    inline
    RGB operator-(const RGB& lhs, const RGB& rhs) noexcept
    {
        RGB result{lhs};
        result -= rhs;
        return result;
    }

    inline
    RGB operator*(const RGB& lhs, const RGB& rhs) noexcept
    {
        RGB result{lhs};
        result *= rhs;
        return result;
    }

    template <typename T>
    RGB operator*(const RGB& lhs, T factor) noexcept
    {
        static_assert(std::is_integral_v<T>);
        RGB result{lhs};
        result *= factor;
        return result;
    }

    template <typename T>
    RGB operator*(T factor, const RGB& rhs) noexcept
    {
        static_assert(std::is_integral_v<T>);
        RGB result{rhs};
        result *= factor;
        return result;
    }

    inline
    std::ostream& operator<<(std::ostream& os, const RGB& color)
    {
        os << color.r << ' ' << color.g << ' ' << color.b;
        return os;
    }

    ///////////////////////////////////////////////////////////////////////////
    // RGBN
    ///////////////////////////////////////////////////////////////////////////

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
    RGBN& RGBN::operator+=(const RGBN& other) noexcept
    {
        r = clamp(r + other.r, 1.f);
        g = clamp(g + other.g, 1.f);
        b = clamp(b + other.b, 1.f);
        return *this;
    }

    inline
    RGBN& RGBN::operator-=(const RGBN& other) noexcept
    {
        r = clamp(r - other.r, 0.f, 1.f);
        g = clamp(g - other.g, 0.f, 1.f);
        b = clamp(b - other.b, 0.f, 1.f);
        return *this;
    }

    inline
    RGBN& RGBN::operator*=(const RGBN& other) noexcept
    {
        r = clamp(r * other.r, 1.f);
        g = clamp(g * other.g, 1.f);
        b = clamp(b * other.b, 1.f);
        return *this;
    }

    template <typename T>
    RGBN& RGBN::operator*=(T other) noexcept
    {
        r = clamp(r * other, 1.f);
        g = clamp(g * other, 1.f);
        b = clamp(b * other, 1.f);
        return *this;
    }

    inline
    float& RGBN::operator[](unsigned short index)
    {
        if (index == 0)
            return r;
        if (index == 1)
            return g;
        if (index == 2)
            return b;
        throw std::out_of_range{"Color index out of range."};
    }

    inline
    float RGBN::operator[](unsigned short index) const
    {
        if (index == 0)
            return r;
        if (index == 1)
            return g;
        if (index == 2)
            return b;
        throw std::out_of_range{"Color index out of range."};
    }

    inline
    bool operator==(const RGBN& lhs, const RGBN& rhs) noexcept
    {
        return lhs.r && rhs.r && lhs.g == rhs.g && lhs.b == rhs.b;
    }

    inline
    bool operator!=(const RGBN& lhs, const RGBN& rhs) noexcept
    {
        return !(lhs == rhs);
    }

    inline
    RGBN operator+(const RGBN& lhs, const RGBN& rhs) noexcept
    {
        RGBN result{lhs};
        result += rhs;
        return result;
    }

    inline
    RGBN operator-(const RGBN& lhs, const RGBN& rhs) noexcept
    {
        RGBN result{lhs};
        result -= rhs;
        return result;
    }

    inline
    RGBN operator*(const RGBN& lhs, const RGBN& rhs) noexcept
    {
        RGBN result{lhs};
        result *= rhs;
        return result;
    }

    template <typename T>
    RGBN operator*(const RGBN& lhs, T factor) noexcept
    {
        RGBN result{lhs};
        result *= factor;
        return result;
    }

    template <typename T>
    RGBN operator*(T factor, const RGBN& rhs) noexcept
    {
        RGBN result{rhs};
        result *= factor;
        return result;
    }

    inline
    std::ostream& operator<<(std::ostream& os, const RGBN& color)
    {
        os << color.r << ' ' << color.g << ' ' << color.b;
        return os;
    }

    ///////////////////////////////////////////////////////////////////////////
    // Hash
    ///////////////////////////////////////////////////////////////////////////

    inline std::size_t hash_value(const RGB& arg)
    {
        std::size_t seed = 0;
        boost::hash_combine(seed, arg.r);
        boost::hash_combine(seed, arg.g);
        boost::hash_combine(seed, arg.b);
        return seed;
    }

    inline std::size_t hash_value(const RGBN& arg)
    {
        std::size_t seed = 0;
        boost::hash_combine(seed, arg.r);
        boost::hash_combine(seed, arg.g);
        boost::hash_combine(seed, arg.b);
        return seed;
    }
} // namespace image

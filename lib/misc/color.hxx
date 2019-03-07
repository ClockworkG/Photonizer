#pragma once

#include "color.hh"

inline
Color::Color(float red, float green, float blue)
    : r(red)
    , g(green)
    , b(blue)
{}

inline
float& Color::operator[](std::size_t index)
{
    switch (index)
    {
    case 0:
        return r;
    case 1:
        return g;
    case 2:
        return b;
    default:
        throw std::out_of_range("Index out of bounds");
    }
}

inline Color& Color::operator+=(const Color& b)
{
    this->r += b.r;
    this->g += b.g;
    this->b += b.b;
    return *this;
}

inline Color& Color::operator-=(const Color& b)
{
    this->r -= b.r;
    this->g -= b.g;
    this->b -= b.b;
    return *this;
}

inline Color& Color::operator*=(const Color& b)
{
    this->r *= b.r;
    this->g *= b.g;
    this->b *= b.b;
    return *this;
}

template <typename T>
inline
Color& Color::operator*=(const T& b)
{
    this->r *= b;
    this->g *= b;
    this->b *= b;
    return *this;
}

inline Color& Color::normalize()
{
    r /= 255.0f;
    g /= 255.0f;
    b /= 255.0f;
    return *this;
}

inline bool operator==(const Color& a, const Color& b)
{
    return a.r == b.r && a.g == b.g && a.b == b.b;
}

inline bool operator!=(const Color& a, const Color& b)
{
    return !(a == b);
}

inline Color operator+(const Color& a, const Color& b)
{
    return Color(a.r + b.r, a.g + b.g, a.b + b.b);
}

inline Color operator-(const Color& a, const Color& b)
{
    return Color(a.r - b.r, a.g - b.g, a.b - b.b);
}

inline Color operator*(const Color& a, const Color& b)
{
    return Color(a.r * b.r, a.g * b.g, a.b * b.b);
}

template <typename T>
inline Color operator*(const Color& a, const T& b)
{
    return Color(a.r * b, a.g * b, a.b * b);
}

inline std::ostream& operator<<(std::ostream& out, const Color& a)
{
    out.fill(' ');
    int width = 8;
    out << "<Color> r: " << std::setw(width) << std::left << a.r
        << " g: " << std::setw(width) << std::left << a.g
        << " b: " << std::setw(width) << std::left << a.b;
    return out;
}

inline std::size_t hash_value(const Color& arg)
{
    std::size_t seed = 0;
    boost::hash_combine(seed, arg.r);
    boost::hash_combine(seed, arg.g);
    boost::hash_combine(seed, arg.b);
    return seed;
}

#include "color.hh"

Color::Color(float red, float green, float blue)
    : r(red)
    , g(green)
    , b(blue)
{}

float& Color::operator[](size_t index)
{
    if (index == 0)
        return r;
    else if (index == 1)
        return g;
    else if (index == 2)
        return b;
    else
        throw std::out_of_range("Index out of bounds");
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
Color operator*(const Color& a, const T& b)
{
    return Color(a.r * b, a.g * b, a.b * b);
}

std::ostream& operator<<(std::ostream& out, const Color& a)
{
    return out;
}

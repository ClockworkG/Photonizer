#pragma once

#include <functional>
#include <iomanip>
#include <ostream>
#include <stdexcept>

struct Color
{
    float r;
    float g;
    float b;

    Color(float red = 0, float green = 0, float blue = 0);

    Color& operator+=(const Color& b);
    Color& operator-=(const Color& b);
    Color& operator*=(const Color& b);

    template <typename T>
    Color& operator*=(const T& b);

    Color& normalize();
};

bool operator==(const Color& a, const Color& b);
bool operator!=(const Color& a, const Color& b);

Color operator+(const Color& a, const Color& b);
Color operator-(const Color& a, const Color& b);
Color operator*(const Color& a, const Color& b);

template <typename T>
Color operator*(const Color& a, const T& b);

std::ostream& operator<<(std::ostream& out, const Color& a);

#include "color.hxx"

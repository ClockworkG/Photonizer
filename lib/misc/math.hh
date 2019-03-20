#pragma once

#include <cmath>
#include <type_traits>

#include "vector3.hh"

template <int Steps>
class BaseConverter
{
public:
    BaseConverter()
    {
        for (int i = 0; i < Steps; i++)
        {
            double angle = static_cast<double>(i) * (1.f / Steps) * M_PI;
            costheta[i] = cos(angle);
            sintheta[i] = sin(angle);
            cosphi[i] = cos(2.f * angle);
            sinphi[i] = sin(2.f * angle);
        }
    }

    Vector3f operator()(uint8_t phi, uint8_t theta) const;

private:
    std::array<float, Steps> costheta;
    std::array<float, Steps> sintheta;
    std::array<float, Steps> cosphi;
    std::array<float, Steps> sinphi;
};

template <typename T>
T clamp(T value, T upper)
{
    if (value > upper)
        return upper;
    return value;
}

template <typename T>
std::enable_if_t<!std::is_unsigned_v<T>, T> clamp(T value, T lower, T upper)
{
    if (value < lower)
        return lower;
    if (value > upper)
        return upper;
    return value;
}

template <typename T>
std::enable_if_t<std::is_unsigned_v<T>, T> clamp(T value, T, T upper)
{
    if (value > upper)
        return upper;
    return value;
}

template <int Steps>
inline
Vector3f BaseConverter<Steps>::operator()(uint8_t phi, uint8_t theta) const
{
    return Vector3f
    (
        sintheta[theta] * cosphi[phi],
        sintheta[theta] * sinphi[phi],
        costheta[theta]
    );
}

inline
std::pair<uint8_t, uint8_t> polar_convert(const Vector3f& vect)
{
    float theta_f = static_cast<int>(acos(vect.z)) * (static_cast<float>(256) / M_PI);
    uint8_t theta = clamp<uint16_t>(theta_f, 255);

    float phi_f = static_cast<int>(atan2(vect.y, vect.x) * (static_cast<float>(256) / (2.0 / M_PI)));
    uint8_t phi = 0;

    if (phi_f > 255.f)
        phi = 255;
    else if (phi_f < 0)
        phi = phi_f + 256;
    else
        phi = phi_f;

    return std::make_pair(phi, theta);
}

inline
Vector3f polar_convert(uint8_t phi, uint8_t theta)
{
    static BaseConverter<256> converter;
    return converter(phi, theta);
}

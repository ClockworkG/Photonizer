#pragma once

#include <iomanip>

#include "vector3.hh"

constexpr static inline auto epsilon = 0.0000001f;

template <typename T>
constexpr inline
Vector3<T>::Vector3(T x, T y, T z)
    : x(x)
    , y(y)
    , z(z)
{}

template <typename T>
T& Vector3<T>::operator[](size_t index)
{
    if (index == 0)
        return x;
    else if (index == 1)
        return y;
    else if (index == 2)
        return z;
    else
        throw std::out_of_range("Index out of bounds");
}

template <typename T>
inline Vector3<T>& Vector3<T>::operator+=(const Vector3<T>& b)
{
    this->x += b.x;
    this->y += b.y;
    this->z += b.z;
    return *this;
}

template <typename T>
inline Vector3<T>& Vector3<T>::operator-=(const Vector3<T>& b)
{
    this->x -= b.x;
    this->y -= b.y;
    this->z -= b.z;
    return *this;
}

template <typename T>
inline T Vector3<T>::norm()
{
    return std::sqrt(x * x + y * y + z * z);
}

template <typename T>
inline Vector3<T>& Vector3<T>::normalize()
{
    T norm = this->norm();
    if ((float)norm != 0.0f)
    {
        x /= norm;
        y /= norm;
        z /= norm;
    }
    return *this;
}

template <typename T>
inline bool operator==(const Vector3<T>& a, const Vector3<T>& b)
{
    return a.x == b.x && a.y == b.y && a.z == b.z;
}

template<>
inline bool operator==(const Vector3<float>& a, const Vector3<float>& b)
{
    return (a.x < b.x + epsilon && a.x > b.x - epsilon
            && a.y < b.y + epsilon && a.y > b.y - epsilon
            && a.z < b.z + epsilon && a.z > b.z - epsilon);
}

template <typename T>
inline bool operator!=(const Vector3<T>& a, const Vector3<T>& b)
{
    return !(a == b);
}

template <typename T>
inline Vector3<T> operator+(const Vector3<T>& a, const Vector3<T>& b)
{
    return Vector3(a.x + b.x, a.y + b.y, a.z + b.z);
}

template <typename T>
inline Vector3<T> operator-(const Vector3<T>& a, const Vector3<T>& b)
{
    return Vector3(a.x - b.x, a.y - b.y, a.z - b.z);
}

template <typename T>
inline T operator*(const Vector3<T>& a, const Vector3<T>& b)
{
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

template <typename T>
inline Vector3<T> operator^(const Vector3<T>& a, const Vector3<T>& b)
{
    return Vector3(a.y * b.z - a.z * b.y,
                   a.z * b.x - a.x * b.z,
                   a.x * b.y - a.y * b.x);
}

template <typename T, typename U>
Vector3<T> operator*(const Vector3<T>& a, const U& b)
{
    return Vector3(a.x * b, a.y * b, a.z * b);
}

template <typename T>
std::ostream& operator<<(std::ostream& out, const Vector3<T>& a)
{
    out << '(' << a.x << ',' << a.y << ',' << a.z << ')';
    return out;
}

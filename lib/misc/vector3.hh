#pragma once

#include <ostream>
#include <stdexcept>
#include <cmath>

template <typename T>
class Vector3
{
public:
    T x;
    T y;
    T z;

    Vector3(T x, T y, T z);

    T& operator[](size_t index);

    Vector3<T>& operator+=(const Vector3<T>& a);
    Vector3<T>& operator-=(const Vector3<T>& a);

    T norm();
    Vector3<T>& normalize();
};

using Vector3f = Vector3<float>;
using Vector3i = Vector3<int>;

template <typename T>
bool operator==(const Vector3<T>& a, const Vector3<T>& b);
template <typename T>
bool operator!=(const Vector3<T>& a, const Vector3<T>& b);

template <typename T>
Vector3<T> operator+(const Vector3<T>& a, const Vector3<T>& b);
template <typename T>
Vector3<T> operator-(const Vector3<T>& a, const Vector3<T>& b);

template <typename T>
T operator*(const Vector3<T>& a, const Vector3<T>& b);
template <typename T>
Vector3<T> operator^(const Vector3<T>& a, const Vector3<T>& b);

template <typename T>
std::ostream& operator<<(std::ostream& out, const Vector3<T>& a);

#include "vector3.hxx"

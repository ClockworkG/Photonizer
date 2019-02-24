#pragma once

#include <ostream>
#include <stdexcept>
#include <cmath>

template <typename T>
struct Vector3
{
    T x;
    T y;
    T z;

    Vector3(T x = 0, T y = 0, T z = 0);

    T& operator[](size_t index);

    Vector3<T>& operator+=(const Vector3<T>& b);
    Vector3<T>& operator-=(const Vector3<T>& b);

    T norm();
    Vector3<T>& normalize();
};

using Vector3i = Vector3<int>;
using Vector3f = Vector3<float>;
using Vector3d = Vector3<double>;

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

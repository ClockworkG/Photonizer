#pragma once

#include "vector3.hh"

template <typename T>
Vector3<T>::Vector3(T x, T y, T z)
    : x(x), y(y), z(z)
{}


template <typename T>
bool operator==(Vector3<T> const& a, Vector3<T> const& b)
{
    return a.x == b.x && a.y == b.y && a.z == b.z;
}

template <typename T>
bool operator!=(Vector3<T> const& a, Vector3<T> const& b)
{
    return !(a == b);
}

#pragma once

#include "ray.hh"

template <typename T>
inline
Ray<T>::Ray(const Vector3<T>& o, const Vector3<T>& dir)
    : o(o)
    , dir(dir)
{}

template <typename T>
inline bool operator==(const Ray<T>& a, const Ray<T>& b)
{
    return a.o == b.o && a.dir == b.dir;
}

template <typename T>
inline bool operator!=(const Ray<T>& a, const Ray<T>& b)
{
    return !(a == b);
}

template <typename T>
std::ostream& operator<<(std::ostream& out, const Ray<T>& a)
{
    out << a.o << " | " << a.dir;
    return out;
}

#pragma once

#include "vector3.hh"

template <typename T>
struct Ray
{
    Vector3<T> o;
    Vector3<T> dir;

    Ray(const Vector3<T>& o, const Vector3<T>& dir);
};

using Rayf = Ray<float>;
using Rayi = Ray<int>;

template <typename T>
bool operator==(const Ray<T>& a, const Ray<T>& b);
template <typename T>
bool operator!=(const Ray<T>& a, const Ray<T>& b);

template <typename T>
std::ostream& operator<<(std::ostream& out, const Ray<T>& a);


#include "ray.hxx"

#pragma once

#include "vector3.hh"

template <typename T>
class Ray
{
public:
    Vector3<T> o;
    Vector3<T> dir;

    Ray(Vector3<T> o, Vector3<T> dir);
};

using Rayf = Ray<float>;

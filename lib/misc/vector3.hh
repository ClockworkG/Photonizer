#pragma once

template <typename T>
class Vector3
{
public:
    T x;
    T y;
    T z;

    Vector3(T x, T y, T z);
};

using Vector3f = Vector3<float>;

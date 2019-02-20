#include "ray.hh"

template <typename T>
Ray<T>::Ray(Vector3<T> o, Vector3<T> dir)
    : o(o), dir(dir)
{}

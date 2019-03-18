#pragma once

#include <type_traits>

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

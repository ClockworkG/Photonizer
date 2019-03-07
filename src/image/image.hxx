#pragma once

#include "image.hh"

namespace image
{
    template <typename V>
    Image<V>::Image(height_t height, width_t width)
        : pixels_(height, typename pixels_t::value_type(width))
    {}

    template <typename V>
    inline
    auto Image<V>::operator[](const point_t& point) const -> const_reference
    {
        auto [x, y] = point;
        return pixels_[x][y];
    }

    template <typename V>
    inline
    auto Image<V>::operator[](const point_t& point) -> reference
    {
        auto [x, y] = point;
        return pixels_[x][y];
    }

    template <typename V>
    inline
    auto Image<V>::get_width() const -> width_t
    {
        return pixels_[0].size();
    }

    template <typename V>
    inline
    auto Image<V>::get_height() const -> height_t
    {
        return pixels_.size();
    }

} // namespace image

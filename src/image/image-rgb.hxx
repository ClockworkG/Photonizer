/**
 * \file image/image-rgb.hxx
 * \brief Inline implementation of ImageRGB class.
 */
#pragma once

#include "image-rgb.hh"

namespace image
{
    ImageRGB::ImageRGB(height_t height, width_t width)
        : pixels_(height, typename pixels_t::value_type(width))
    {}

    inline
    auto ImageRGB::operator[](const point_t& point) const -> const_reference
    {
        auto [x, y] = point;
        return pixels_[x][y];
    }

    inline
    auto ImageRGB::operator[](const point_t& point) -> reference
    {
        auto [x, y] = point;
        return pixels_[x][y];
    }

    inline
    auto ImageRGB::get_width() const -> width_t
    {
        return pixels_[0].size();
    }

    inline
    auto ImageRGB::get_height() const -> height_t
    {
        return pixels_.size();
    }

} // namespace image

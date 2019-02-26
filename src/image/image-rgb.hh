/**
 * \file image/image-rgb.hh
 * \brief Define a class to work with RGB images.
 */
#pragma once

#include <type_traits>
#include <vector>

#include "color.hh"

/// Responsible for handling images.
namespace image
{
    /// Represents an image with a matrix of RGB values.
    class ImageRGB
    {
    public:
        /// Height type.
        using height_t = unsigned short;
        /// Width type.
        using width_t = unsigned short;
        /// Pixel position in the image.
        using point_t = std::pair<height_t, width_t>;
        /// Value carried by a pixel.
        using value_t = Color;
        /// Position and value of a pixel.
        using pixel_t = std::pair<point_t, value_t>;

        /// Reference on a pixel's value.
        using reference = value_t&;
        /// Const-reference on a pixel's value.
        using const_reference = const value_t&;

        /** \name Ctors & dtor.
         * \{ */
        ImageRGB(height_t height, width_t width);
        ~ImageRGB() = default;
        ImageRGB(const ImageRGB&) = default;
        ImageRGB(ImageRGB&&) noexcept = default;
        ImageRGB& operator=(const ImageRGB&) = default;
        ImageRGB& operator=(ImageRGB&&) noexcept = default;
        /** \} */

        /** \name Accessors.
         * \{ */
        const_reference operator[](const point_t& point) const;
        reference       operator[](const point_t& point);
        height_t        get_height() const;
        width_t         get_width() const;
        /** \} */

    private:
        /// Type of the pixel matrix.
        using pixels_t = std::vector<std::vector<value_t>>;

        /// Matrix containing image's pixels.
        pixels_t pixels_;
    };
} // namespace image

#include "image-rgb.hxx"

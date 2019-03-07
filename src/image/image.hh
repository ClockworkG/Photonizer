#pragma once

#include <type_traits>
#include <vector>

namespace image
{
    template <typename ValueType>
    class Image
    {
    public:
        /// Height type.
        using height_t = unsigned short;
        /// Width type.
        using width_t = unsigned short;
        /// Pixel position in the image.
        using point_t = std::pair<height_t, width_t>;
        /// Value carried by a pixel.
        using value_t = ValueType;
        /// Position and value of a pixel.
        using pixel_t = std::pair<point_t, value_t>;

        using reference = value_t&;
        using const_reference = const value_t&;

        /** \name Ctors and dtors.
         * \{ */
        Image(height_t height, width_t width);
        Image(const Image&) = default;
        Image(Image&&) noexcept = default;
        Image& operator=(const Image&) = default;
        Image& operator=(Image&&) noexcept = default;
        /** \} */

        /** \name Accessors.
         * \{ */
        const_reference operator[](const point_t& point) const;
        reference       operator[](const point_t& point);
        height_t        get_height() const;
        width_t         get_width() const;
        /** \} */

    protected:
        /// Type of the pixel matrix.
        using pixels_t = std::vector<std::vector<value_t>>;

        /// Matrix containing image's pixels.
        pixels_t pixels_;
    };
} // namespace image

#include "image.hxx"

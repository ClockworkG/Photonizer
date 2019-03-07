#pragma once

#include <algorithm>
#include <type_traits>
#include <vector>

#include "hsv.hh"
#include "image-rgb.hh"
#include "image.hh"

namespace image
{
    template <typename T>
    class Heatmap : public Image<T>
    {
        static_assert(std::is_integral_v<T> || std::is_floating_point_v<T>);
        using super_t = Image<T>;

    public:
        using typename super_t::height_t;
        using typename super_t::width_t;
        using typename super_t::point_t;
        using typename super_t::value_t;
        using typename super_t::pixel_t;
        using typename super_t::reference;
        using typename super_t::const_reference;

        /** \name Ctors & dtor.
         * \{ */
        Heatmap(height_t height, width_t width);
        ~Heatmap() = default;
        Heatmap(const Heatmap&) = default;
        Heatmap(Heatmap&&) = default;
        Heatmap& operator=(const Heatmap&) = default;
        Heatmap& operator=(Heatmap&&) = default;
        /** \} */

        operator ImageRGB() const;
    };
}

#include "heatmap.hxx"

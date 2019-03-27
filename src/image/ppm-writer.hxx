#pragma once

#include "ppm-writer.hh"

#include <stdexcept>

#include "image-rgb.hh"

namespace image
{
    template<>
    inline
    void PPMWriter<ImageRGB>::write(std::ostream& os, const image_t& image)
    {
        os << "P3\n"
           << image.get_width() << ' ' << image.get_height() << "\n"
           << "255\n";

        auto print_color = [&os, &image](auto x, auto y, char trailing = ' ')
        {
            auto color = image[{x, y}];
            os << static_cast<unsigned int>(color.r)
               << ' '
               << static_cast<unsigned int>(color.g)
               << ' '
               << static_cast<unsigned int>(color.b)
               << trailing;
        };
        for (image_t::height_t x = 0; x < image.get_height(); x++)
        {
            for (image_t::width_t y = 0; y < image.get_width() - 1; y++)
                print_color(x, y);

            print_color(x, image.get_width() - 1, '\n');
        }
    }
} // namespace image

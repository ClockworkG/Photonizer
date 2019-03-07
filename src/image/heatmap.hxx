#pragma once

#include "heatmap.hh"

namespace image
{
    template <typename T>
    inline
    Heatmap<T>::Heatmap(height_t height, width_t width)
        : super_t(height, width)
    {}

    template <typename T>
    inline
    Heatmap<T>::operator ImageRGB() const
    {
        T maximum{};
        T minimum{};

        {
            auto maximums = std::vector<T>(super_t::get_height());
            auto minimums = std::vector<T>(super_t::get_height());

            std::transform(this->pixels_.begin(), this->pixels_.end(),
                           maximums.begin(),
                           [](auto x)
                           {
                             return *std::max_element(x.begin(), x.end());
                           });
            std::transform(this->pixels_.begin(), this->pixels_.end(),
                           minimums.begin(),
                           [](auto x)
                           {
                             return *std::min_element(x.begin(), x.end());
                           });
            maximum = *std::max_element(maximums.begin(), maximums.end());
            minimum = *std::min_element(minimums.begin(), minimums.end());
        }

        ImageRGB result{super_t::get_height(), super_t::get_width()};
        for (std::size_t i = 0; i < super_t::get_height(); i++)
        {
            for (std::size_t j = 0; j < super_t::get_width(); j++)
            {
                HSV color{0, 1, 1};
                auto value = this->pixels_[i][j];
                auto ratio = (value - minimum) / (maximum - minimum);

                color.set_h((1 - ratio) * 0.7);
                result[{i, j}] = static_cast<RGB>(color);
            }
        }

        return result;
    }
} // namespace image

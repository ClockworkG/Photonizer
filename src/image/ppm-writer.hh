#pragma once

#include <ostream>

#include "image-writer.hh"

namespace image
{
    template <typename ImageType>
    class PPMWriter : public ImageWriter<ImageType>
    {
        using super_t = ImageWriter<ImageType>;

    public:
        using image_t = typename super_t::image_t;

        /** \name Ctors & dtors.
         * \{ */
        PPMWriter() noexcept = default;
        virtual ~PPMWriter() = default;
        /** \} */

        void write(std::ostream& os, const image_t& image) final;
    };
} // namespace image

#include "ppm-writer.hxx"

/**
 * \file image/ppm-writer.hh
 * \brief Define an implementation of ImageWriter for PPM.
 */
#pragma once

#include <ostream>

#include "image-writer.hh"

namespace image
{
    /// Write images into the PPM file format.
    template <typename ImageType>
    class PPMWriter : public ImageWriter<ImageType>
    {
        /// Super type.
        using super_t = ImageWriter<ImageType>;

    public:
        /// Type of the image to write.
        using image_t = typename super_t::image_t;

        /** \name Ctors & dtors.
         * \{ */
        PPMWriter() noexcept = default;
        virtual ~PPMWriter() = default;
        PPMWriter(const PPMWriter&) = delete;
        PPMWriter(PPMWriter&&) = delete;
        PPMWriter& operator=(const PPMWriter&) = delete;
        PPMWriter& operator=(PPMWriter&&) = delete;
        /** \} */

        /// Write the image in the output stream as a PPM.
        void operator()(std::ostream& os, const image_t& image) final;
    };
} // namespace image

#include "ppm-writer.hxx"

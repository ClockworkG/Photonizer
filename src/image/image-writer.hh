/**
 * \file image/image-writer.hh
 * \brief Define an interface to output an image.
 */
#pragma once

#include <ostream>

namespace image
{
    /// Image writer templated on the image type to write.
    template <typename ImageType>
    class ImageWriter
    {
    public:
        /// Type of the image to write.
        using image_t = ImageType;

        /** \name Ctors & dtor.
         * \{ */
        ImageWriter() noexcept = default;
        virtual ~ImageWriter() = default;
        ImageWriter(const ImageWriter&) = delete;
        ImageWriter(ImageWriter&&) = delete;
        ImageWriter& operator=(const ImageWriter&) = delete;
        ImageWriter& operator=(ImageWriter&&) = delete;
        /** \} */

        /// Write the specified image to the output stream.
        virtual void operator()(std::ostream& os, const image_t& image) = 0;
    };
} // namespace image

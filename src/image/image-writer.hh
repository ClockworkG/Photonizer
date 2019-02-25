#pragma once

#include <ostream>

namespace image
{
    template <typename ImageType>
    class ImageWriter
    {
    public:
        using image_t = ImageType;

        /** \name Ctors & dtors.
         * \{ */
        ImageWriter() noexcept = default;
        virtual ~ImageWriter() = default;
        /** \} */

        ImageWriter(const ImageWriter&) = delete;
        ImageWriter(ImageWriter&&) = delete;
        ImageWriter& operator=(const ImageWriter&) = delete;
        ImageWriter& operator=(ImageWriter&&) = delete;

        virtual void write(std::ostream& os, const image_t& image) = 0;
    };
} // namespace image

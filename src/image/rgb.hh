#pragma once

#include <array>
#include <ostream>

#include <boost/functional/hash.hpp>

#include "math.hh"

namespace image
{
    struct RGBN;

    struct RGB
    {
        /** \name Ctors & dtor.
         * \{ */
        RGB(uint16_t r_init = 0, uint16_t g_init = 0, uint16_t b_init = 0);
        ~RGB() = default;
        RGB(const RGB&) noexcept = default;
        RGB(RGB&&) noexcept = default;
        RGB& operator=(const RGB&) noexcept = default;
        RGB& operator=(RGB&&) noexcept = default;
        /** \} */

        /** \name Operators.
         * \{ */
        operator RGBN() const noexcept;

        RGB& operator+=(const RGB& other) noexcept;
        RGB& operator-=(const RGB& other) noexcept;
        RGB& operator*=(const RGB& other) noexcept;

        template <typename T>
        RGB& operator*=(T other) noexcept;

        uint16_t& operator[](unsigned short index);
        uint16_t  operator[](unsigned short index) const;
        /** \} */

        uint16_t r;
        uint16_t g;
        uint16_t b;
    };

    struct RGBN
    {

        /** \name Ctors & dtor.
         * \{ */
        RGBN(float r_init = 0, float g_init = 0,
             float b_init = 0);
        ~RGBN() = default;
        RGBN(const RGBN&) noexcept = default;
        RGBN(RGBN&&) noexcept = default;
        RGBN& operator=(const RGBN&) noexcept = default;
        RGBN& operator=(RGBN&&) noexcept = default;
        /** \} */

        /** \name Operators.
         * \{ */
        operator RGB() const noexcept;

        RGBN& operator+=(const RGBN& other) noexcept;
        RGBN& operator-=(const RGBN& other) noexcept;
        RGBN& operator*=(const RGBN& other) noexcept;

        template <typename T>
        RGBN& operator*=(T other) noexcept;

        float& operator[](unsigned short index);
        float  operator[](unsigned short index) const;
        /** \} */

        float r;
        float g;
        float b;
    };

    /** \name RGB operators.
     * \{ */
    bool operator==(const RGB& lhs, const RGB& rhs) noexcept;
    bool operator!=(const RGB& lhs, const RGB& rhs) noexcept;

    RGB operator+(const RGB& lhs, const RGB& rhs) noexcept;
    RGB operator-(const RGB& lhs, const RGB& rhs) noexcept;
    RGB operator*(const RGB& lhs, const RGB& rhs) noexcept;

    template <typename T>
    RGB operator*(const RGB& lhs, T factor) noexcept;

    template <typename T>
    RGB operator*(T factor, const RGB& rhs) noexcept;

    std::ostream& operator<<(std::ostream& os, const RGB& color);
    /** \} */

    /** \name RGBN operators.
     * \{ */
    bool operator==(const RGBN& lhs, const RGBN& rhs) noexcept;
    bool operator!=(const RGBN& lhs, const RGBN& rhs) noexcept;

    RGBN operator+(const RGBN& lhs, const RGBN& rhs) noexcept;
    RGBN operator-(const RGBN& lhs, const RGBN& rhs) noexcept;
    RGBN operator*(const RGBN& lhs, const RGBN& rhs) noexcept;

    template <typename T>
    RGBN operator*(const RGBN& lhs, T factor) noexcept;

    template <typename T>
    RGBN operator*(T factor, const RGBN& rhs) noexcept;

    std::ostream& operator<<(std::ostream& os, const RGBN& color);
    /** \} */

} // namespace image

#include "rgb.hxx"

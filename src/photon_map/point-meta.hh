#pragma once

#include <type_traits>

#include "vector3.hh"

namespace photon
{
    template <typename ValueType>
    struct point_traits
    {
        using point_t = Vector3f;
        using index_t = uint8_t;
        static inline constexpr auto dimension = point_t::dimension;
    };

    template <typename ValueType>
    struct PointComparePolicy
    {
        static_assert(
            point_traits<ValueType>::dimension != 0,
            "Dimension cannot be 0."
        );
        static_assert(
            std::is_convertible_v<
                const ValueType,
                typename point_traits<ValueType>::point_t
            >,
            "ValueType must be implicitly convertible to a position."
        );
        static_assert(
            std::is_copy_constructible_v<ValueType>,
            "ValueType must be copy constructible."
        );
        static_assert(
            std::is_integral_v<typename point_traits<ValueType>::index_t>
        );

        static typename point_traits<ValueType>::point_t
        to_point(const ValueType& value) noexcept
        {
            return static_cast<typename point_traits<ValueType>::point_t>(
                    value
            );
        }

        static bool
        less(const ValueType& a, const ValueType& b,
             typename point_traits<ValueType>::index_t index) noexcept
        {
            return to_point(a)[index] < to_point(b)[index];
        }

        static typename point_traits<ValueType>::index_t
        next(typename point_traits<ValueType>::index_t index) noexcept
        {
            return (index + 1) % point_traits<ValueType>::dimension;
        }
    };
} // namespace photon

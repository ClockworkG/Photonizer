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
        using atom_t = float;
        constexpr static inline auto dimension = point_t::dimension;
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
            std::is_integral_v<typename point_traits<ValueType>::index_t>,
            "Index type must be integral."
        );
        static_assert(
            std::is_integral_v<typename point_traits<ValueType>::atom_t>
            || std::is_floating_point_v<typename point_traits<ValueType>::atom_t>,
            "Atom type must be a number."
        );
        static_assert(
            std::is_convertible_v<
                typename point_traits<ValueType>::point_t,
                bool
            >,
            "Point type must have a null value."
        );

        static typename point_traits<ValueType>::atom_t
        squared_distance(const ValueType& lhs, const ValueType& rhs) noexcept
        {
            typename point_traits<ValueType>::atom_t square{};
            for (typename point_traits<ValueType>::index_t i = 0;
                 i < point_traits<ValueType>::dimension;
                 i++)
            {
                square += ((to_point(lhs)[i] - to_point(rhs)[i])
                           * (to_point(lhs)[i] - to_point(rhs)[i]));
            }

            return square < 0 ? -square : square;
        }

        static typename point_traits<ValueType>::point_t
        to_point(const ValueType& value) noexcept
        {
            return static_cast<typename point_traits<ValueType>::point_t>(
                    value
            );
        }

        static bool
        is_not_null(const ValueType& a) noexcept
        {
            return static_cast<bool>(to_point(a));
        }

        static bool
        less(const ValueType& a, const ValueType& b,
             typename point_traits<ValueType>::index_t index) noexcept
        {
            return to_point(a)[index] < to_point(b)[index];
        }

        static bool
        equal(const ValueType& a, const ValueType& b) noexcept
        {
            return to_point(a) == to_point(b);
        }

        static typename point_traits<ValueType>::index_t
        next(typename point_traits<ValueType>::index_t index) noexcept
        {
            return (index + 1) % point_traits<ValueType>::dimension;
        }
    };
} // namespace photon

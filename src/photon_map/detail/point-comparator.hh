#pragma once

#include <algorithm>
#include <array>

#include "point-meta.hh"

namespace photon::detail
{
    template <typename ValueType>
    class PointComparator
    {
        using self_t = PointComparator<ValueType>;
        friend std::hash<self_t>;

    public:
        template <typename Iterator>
        PointComparator(Iterator begin, Iterator end)
        {
            std::size_t index = 0;
            for (auto it = begin; it != end; it++)
                indexes_[index++] = *it;
        }

        ~PointComparator() = default;
        PointComparator(const PointComparator&) = default;
        PointComparator(PointComparator&&) = default;
        PointComparator& operator=(const PointComparator&) = default;
        PointComparator& operator=(PointComparator&&) = default;

        bool operator()(const ValueType& lhs, const ValueType& rhs) const noexcept
        {
            auto lhs_point = PointComparePolicy<ValueType>::to_point(lhs);
            auto rhs_point = PointComparePolicy<ValueType>::to_point(rhs);
            for (const auto index : indexes_)
            {
                if (lhs_point[index] == rhs_point[index])
                    continue;

                return lhs_point[index] < rhs_point[index];
            }

            return false;
        }

        bool operator==(const PointComparator& other) const
        {
            return std::equal(indexes_.begin(), indexes_.end(),
                              other.indexes_.begin());
        }

    private:
        std::array<
            typename point_traits<ValueType>::index_t,
            point_traits<ValueType>::dimension
        > indexes_;
    };

} // namespace photon::detail

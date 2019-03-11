#pragma once

#include "kd-tree.hh"

namespace photon
{
    template <typename V>
    template <typename It>
    KDTree<V>::KDTree(It begin, It end)
        : data_(detail::make_balanced_tree<V>(begin, end))
    {}

    template <typename V>
    auto KDTree<V>::data() const noexcept -> const data_type&
    {
        return data_;
    }

    template <typename V>
    auto KDTree<V>::nearest(const point_t&) const -> Heap<value_type>
    {
        // FIXME...
        return Heap<value_type>{};
    }

    template <typename V>
    std::ostream& operator<<(std::ostream& os, const KDTree<V>& tree)
    {
        const auto& data = tree.data();

        os << "digraph {\n";
        for (std::size_t i = 1; i < data.size(); i++)
        {
            std::size_t next = 2 * i;
            if (next < data.size()
                && PointComparePolicy<V>::is_not_null(data[next]))
            {
                os << '"' << PointComparePolicy<V>::to_point(data[i])
                   << "\" -> \""
                   << PointComparePolicy<V>::to_point(data[next]) << "\"\n";
            }

            if (next + 1 < data.size()
                && PointComparePolicy<V>::is_not_null(data[next + 1]))
            {
                os << '"' << PointComparePolicy<V>::to_point(data[i])
                   << "\" -> \""
                   << PointComparePolicy<V>::to_point(data[next + 1]) << "\"\n";
            }
        }
        os << "}\n";

        return os;
    }
} // namespace photon

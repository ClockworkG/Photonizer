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
    void KDTree<V>::nearest_(const point_t& query,
                             DistanceHeap<value_type>& heap,
                             atom_t max_dist,
                             std::size_t index) const
    {
        const auto& point = data_[index];
        if (index >= data_.size() || !PointComparePolicy<V>::is_not_null(point))
            return;

        if (PointComparePolicy<V>::less(query,
                                        point, get_splitting_dimension(index)))
            nearest_(query, heap, max_dist, 2 * index);
        else
            nearest_(query, heap, max_dist, 2 * index + 1);

        auto dist = PointComparePolicy<V>::squared_distance(query, point);
        if (dist < max_dist)
            heap.insert(std::make_pair(point, dist));
    }

    template <typename V>
    auto KDTree<V>::nearest(const point_t& query,
                            std::size_t max_count,
                            atom_t max_dist) const
        -> DistanceHeap<value_type>
    {
        (void)max_dist;
        DistanceHeap<value_type> heap(max_count);
        nearest_(query, heap, max_dist * max_dist);
        return heap;
    }

    template <typename V>
    auto KDTree<V>::get_splitting_dimension(std::size_t index) const noexcept
        -> typename point_traits<value_type>::index_t
    {
        typename point_traits<value_type>::index_t power_of_two = std::log2(index);
        return index % point_traits<value_type>::dimension;
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

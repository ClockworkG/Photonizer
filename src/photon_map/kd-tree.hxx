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
    KDTree<V>::KDTree(size_type size)
        : data_(size)
    {}

    template <typename V>
    inline
    auto KDTree<V>::data() const noexcept -> const data_type&
    {
        return data_;
    }

    template <typename V>
    inline
    auto KDTree<V>::data() noexcept -> data_type&
    {
        return data_;
    }

    template <typename V>
    inline
    void KDTree<V>::nearest_(const point_t& query,
                             DistanceHeap<value_type>& heap,
                             atom_t& max_dist,
                             std::size_t splitting,
                             std::size_t index) const
    {
        if (is_in_tree(2 * index + 1))
        {
            std::size_t next = PointComparePolicy<V>::next(splitting);
            float dist1 = query[splitting]
                          - PointComparePolicy<V>::to_point(data_[index])[splitting];

            if (dist1 > 0.f)
            {
                nearest_(query, heap, max_dist, next, 2 * index + 1);
                if (dist1 * dist1 < max_dist)
                    nearest_(query, heap, max_dist, next, 2 * index);
            }
            else
            {
                nearest_(query, heap, max_dist, next, 2 * index);
                if (dist1 * dist1 < max_dist)
                    nearest_(query, heap, max_dist, next, 2 * index + 1);
            }
        }

        auto squared = PointComparePolicy<V>::squared_distance(query,
                                                               data_[index]);
        if (squared < max_dist)
        {
            if (!heap.insert(std::make_pair(data_[index], squared)))
                max_dist = heap.top().second;
        }
    }

    template <typename V>
    auto KDTree<V>::nearest(const point_t& query,
                            std::size_t max_count,
                            atom_t max_dist) const
        -> DistanceHeap<value_type>
    {
        DistanceHeap<value_type> heap(max_count);
        max_dist *= max_dist;
        nearest_(query, heap, max_dist, 0);
        return heap;
    }

    template <typename V>
    inline
    bool KDTree<V>::is_in_tree(std::size_t index) const noexcept
    {
        if (index >= data_.size())
            return false;

        return PointComparePolicy<V>::is_not_null(data_[index]);
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

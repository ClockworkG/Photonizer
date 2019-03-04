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
} // namespace photon

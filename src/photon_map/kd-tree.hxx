#pragma once

#include "kd-tree.hh"

namespace photon
{
    template <typename V>
    template <typename Iterator>
    KDTree<V>::KDTree(Iterator begin, Iterator end)
        : root_{nullptr}
    {}

    template <typename V>
    bool KDTree<V>::empty() const noexcept
    {
        return root_ == nullptr;
    }

    template <typename V>
    KDTree<V>::operator bool() const noexcept
    {
        return !empty();
    }
} // namespace photon

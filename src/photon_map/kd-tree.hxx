#pragma once

#include "kd-tree.hh"

namespace photon
{
    template <unsigned K, typename V>
    template <typename Iterator>
    KDTree<K, V>::KDTree(Iterator begin, Iterator end)
        : root_{nullptr}
    {}
} // namespace photon

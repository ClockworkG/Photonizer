#pragma once

#include "brown.hh"

namespace photon
{
    template <typename V, typename It>
    KDTree<V> make_balanced_tree(It begin, It end)
    {
        detail::BrownAlgorithm<V> brown(begin, end);
        return brown();
    }
} // namespace photon

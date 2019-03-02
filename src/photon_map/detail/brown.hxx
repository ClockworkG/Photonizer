#pragma once

#include "brown.hh"

namespace photon::detail
{
    template <typename V, typename It>
    KDTree<V> make_balanced_tree(It begin, It end)
    {
        std::vector<V> tuples{};
        std::copy(begin, end, std::begin(tuples));
    }
} // namespace photon::detail

#pragma once

#include <algorithm>
#include <vector>

#include "kd-tree.hh"
#include "point-meta.hh"
#include "detail/brown-algorithm.hh"

namespace photon
{
    template <typename ValueType, typename Iterator>
    KDTree<ValueType> make_balanced_tree(Iterator begin, Iterator end);
} // namespace photon

#include "brown.hxx"

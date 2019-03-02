#pragma once

#include <algorithm>
#include <vector>

#include "kd-tree.hh"
#include "point-meta.hh"

namespace photon::detail
{
    template <typename ValueType, typename Iterator>
    KDTree<ValueType> make_balanced_tree(Iterator begin, Iterator end);
} // namespace photon::detail

#include "brown.hxx"

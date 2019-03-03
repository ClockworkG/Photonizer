#pragma once

#include <algorithm>
#include <unordered_map>
#include <numeric>
#include <vector>

#include "kd-tree.hh"
#include "point-comparator.hh"

namespace photon::detail
{
    template <typename ValueType>
    class BrownAlgorithm
    {
        using value_t = ValueType;
        using index_t = typename point_traits<ValueType>::index_t;
        using comp_t = PointComparator<ValueType>;
        using indexes_t = std::vector<std::size_t>;

    public:
        using tree_t = KDTree<value_t>;

        template <typename Iterator>
        BrownAlgorithm(Iterator begin, Iterator end);

        tree_t operator()();

    private:
        void build_initial_indices();
        void split_and_build(tree_t& tree);

        std::vector<value_t>   values_;
        std::vector<comp_t>    comparators_;
        std::vector<indexes_t> initial_indices_;
        const index_t          cardinality_;
    };
} // namespace photon::detail

#include "brown-algorithm.hxx"

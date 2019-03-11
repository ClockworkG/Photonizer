#pragma once

#include <algorithm>
#include <numeric>
#include <vector>

#include "point-meta.hh"
#include "point-comparator.hh"

namespace photon
{
    template <typename V>
    class KDTree;
}

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
        using data_t = typename KDTree<ValueType>::data_type;

        template <typename Iterator>
        BrownAlgorithm(Iterator begin, Iterator end);

        data_t operator()();

    private:
        void build_initial_indices();
        void split_and_build(data_t& tree, std::size_t begin,
                             std::size_t end, std::size_t pos,
                             std::size_t axis, bool threaded = false);

        std::vector<value_t>   values_;
        std::vector<comp_t>    comparators_;
        std::vector<indexes_t> initial_indices_;
        const index_t          cardinality_;
    };

    template <typename ValueType, typename Iterator>
    auto make_balanced_tree(Iterator begin, Iterator end)
        -> typename KDTree<ValueType>::data_type;
} // namespace photon

#include "brown.hxx"

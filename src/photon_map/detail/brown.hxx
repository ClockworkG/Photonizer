#pragma once

#include <iostream>
#include <iomanip>

#include "brown.hh"

namespace photon::detail
{
    template <typename V, typename It>
    auto make_balanced_tree(It begin, It end)
        -> typename KDTree<V>::data_type
    {
        detail::BrownAlgorithm<V> brown(begin, end);
        return brown();
    }

    template <typename V>
    template <typename It>
    BrownAlgorithm<V>::BrownAlgorithm(It begin, It end)
        : values_(std::distance(begin, end) + 1)
        , comparators_{}
        , initial_indices_{}
        , cardinality_(point_traits<V>::dimension)
    {
        comparators_.reserve(cardinality_);
        initial_indices_.reserve(cardinality_);
        std::copy(begin, end, std::begin(values_));
    }

    template <typename V>
    auto BrownAlgorithm<V>::operator()() -> data_t
    {
        data_t tree(values_.size());
        build_initial_indices();
        split_and_build(tree, 0, values_.size(), 1);
        return tree;
    }

    template <typename V>
    void BrownAlgorithm<V>::split_and_build(data_t& tree, std::size_t begin,
                                            std::size_t end, std::size_t pos,
                                            std::size_t axis)
    {
        if (begin >= end)
            return;

        auto middle = begin + (end - begin) / 2;
        auto& values = values_;
        auto& median = values[initial_indices_[axis][middle]];
        auto& comp = comparators_[axis];

        for (std::size_t i = 0; i < initial_indices_.size(); i++)
        {
            if (i == axis)
                continue;

            /*
             * XXX: this all part seems ugly af. It needs a better handling.
             * A try was given with the algorithm `std::stable_partition`.
             * However, this does not seem to work at all. The performance
             * might get heavy here. In case of a slow tree construction,
             * attention should be given to this small part of code.
             */
            std::partition(std::begin(initial_indices_[i]) + begin,
                           std::begin(initial_indices_[i]) + end,
                           [comp, values, median](auto x)
                           {
                           return comp(values[x], median);
                           });
            if (initial_indices_[i][middle] != initial_indices_[axis][middle])
            {
                std::iter_swap(std::begin(initial_indices_[i]) + middle,
                               std::find(initial_indices_[i].begin() + begin,
                                         initial_indices_[i].begin() + end,
                                         initial_indices_[axis][middle]));
            }
            auto& current_comp = comparators_[i];
            std::sort(std::begin(initial_indices_[i]) + begin,
                      std::begin(initial_indices_[i]) + middle,
                      [current_comp, values](auto a, auto b)
                      {
                          return current_comp(values[a], values[b]);
                      });

            std::sort(std::begin(initial_indices_[i]) + middle + 1,
                      std::begin(initial_indices_[i]) + end,
                      [current_comp, values](auto a, auto b)
                      {
                          return current_comp(values[a], values[b]);
                      });
        }

        tree[pos] = std::move(median);

        split_and_build(tree, begin, middle, 2 * pos,
                        (axis + 1) % cardinality_);
        split_and_build(tree, middle + 1, end, 2 * pos + 1,
                        (axis + 1) % cardinality_);
    }

    template <typename V>
    void BrownAlgorithm<V>::build_initial_indices()
    {
        std::vector<index_t> indices(cardinality_);
        std::iota(std::begin(indices), std::end(indices), index_t{});

        for (auto i = 0; i < cardinality_; i++)
        {
            comparators_.emplace_back(std::cbegin(indices), std::cend(indices));
            initial_indices_.emplace_back(values_.size());

            auto& comp = comparators_[i];
            auto& indexes = initial_indices_[i];
            auto& values = values_;
            std::iota(std::begin(indexes), std::end(indexes), 0);
            std::sort(
                      std::begin(indexes), std::end(indexes),
                      [comp, values](auto x, auto y)
                      {
                          return comp(values[x], values[y]);
                      }
            );

            std::rotate(std::begin(indices), std::begin(indices) + 1,
                        std::end(indices));
        }
    }

} // namespace photon

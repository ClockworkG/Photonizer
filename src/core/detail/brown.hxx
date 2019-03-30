#pragma once

#include <functional>
#include <iostream>
#include <iomanip>
#include <thread>

#include "brown.hh"
#include "math.hh"

namespace core::detail
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
        : values_(std::distance(begin, end))
        , comparators_{}
        , initial_indices_{}
        , cardinality_(point_traits<V>::dimension)
    {
        std::copy(begin, end, std::begin(values_));
        auto last = std::unique(std::begin(values_), std::end(values_),
                      [](const auto& a, const auto& b)
                      {
                          return PointComparePolicy<V>::equal(a, b);
                      });
        values_.erase(last, std::end(values_));
        comparators_.reserve(cardinality_);
        initial_indices_.reserve(cardinality_);
    }

    template <typename V>
    auto BrownAlgorithm<V>::operator()() -> data_t
    {
        data_t tree(values_.size() * 2);
        build_initial_indices();
        split_and_build(tree, 0, values_.size(), 1, 0, false);
        return tree;
    }

    template <typename V>
    void BrownAlgorithm<V>::split_and_build(data_t& tree, std::size_t begin,
                                            std::size_t end, std::size_t pos,
                                            std::size_t axis, bool)
    {
        if (begin >= end)
            return;
        else if (end - begin == 1)
        {
            tree[pos] = values_[initial_indices_[axis][begin]];
            return;
        }
        else if (end - begin == 2)
        {
            tree[pos] = values_[initial_indices_[axis][begin]];
            tree[2 * pos] = values_[initial_indices_[axis][begin + 1]];
            return;
        }
        else if (end - begin == 3)
        {
            tree[pos] = values_[initial_indices_[axis][begin + 1]];
            tree[2 * pos] = values_[initial_indices_[axis][begin]];
            tree[2 * pos + 1] = values_[initial_indices_[axis][begin + 2]];
            return;
        }

        auto middle = begin + (end - begin) / 2;
        auto& values = values_;
        auto& median = values[initial_indices_[axis][middle]];
        auto& comp = comparators_[axis];

        for (std::size_t i = 0; i < initial_indices_.size(); i++)
        {
            if (i == axis)
                continue;

            indexes_t newer(end - begin);
            std::size_t lower = 0;
            std::size_t upper = middle - begin + 1;

            newer[middle - begin] = initial_indices_[axis][middle];
            for (std::size_t j = begin; j < end; j++)
            {
                auto val = initial_indices_[i][j];
                if (val == initial_indices_[axis][middle])
                    continue;

                if (comp(values[val], median))
                {
                    newer[lower] = val;
                    lower = clamp(lower + 1, middle - begin - 1);
                }
                else
                {
                    newer[upper] = val;
                    upper = clamp(upper + 1, end - begin - 1);
                }
            }

            std::copy(newer.begin(), newer.end(),
                      std::begin(initial_indices_[i]) + begin);
        }

        tree[pos] = median;

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

} // namespace core

#pragma once

#include "brown-algorithm.hh"

namespace photon::detail
{
    template <typename V>
    template <typename It>
    BrownAlgorithm<V>::BrownAlgorithm(It begin, It end)
        : values_(std::distance(begin, end))
        , initial_indices_{}
        , cardinality_(point_traits<V>::dimension)
    {
        std::copy(begin, end, std::begin(values_));
    }

    template <typename V>
    KDTree<V> BrownAlgorithm<V>::operator()()
    {
        build_initial_indices();
        return KDTree<V>{};
    }

    template <typename V>
    void BrownAlgorithm<V>::build_initial_indices()
    {
        std::vector<index_t> indices(cardinality_);
        std::iota(std::begin(indices), std::end(indices), index_t{});

        for (auto i = 0; i < cardinality_; i++)
        {
            auto value = std::make_pair(
                    comp_t(std::cbegin(indices), std::cend(indices)),
                    indexes_t(values_.size())
            );

            auto [it, inserted] = initial_indices_.insert(std::move(value));
            auto& comp = it->first;
            auto& indexes = it->second;
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
} // namespace photon::detail

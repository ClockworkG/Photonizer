#pragma once

#include <algorithm>
#include <vector>

#include "point-meta.hh"

namespace core
{

    template <typename ValueType>
    class DistanceHeap
    {
    public:
        using elt_t =
            std::pair<ValueType, typename point_traits<ValueType>::atom_t>;
        using data_t = std::vector<elt_t>;
        using size_type = std::size_t;
        using const_reference = const elt_t&;
        using const_iterator = typename data_t::const_iterator;

        DistanceHeap(size_type max_size);
        ~DistanceHeap() = default;
        DistanceHeap(const DistanceHeap&) = default;
        DistanceHeap(DistanceHeap&&) = default;
        DistanceHeap& operator=(const DistanceHeap&) = default;
        DistanceHeap& operator=(DistanceHeap&&) = default;

        bool insert(const elt_t& elt);
        bool insert(elt_t&& elt);

        const elt_t& top() const;

        operator bool() const noexcept;
        size_type size() const noexcept;

        const_iterator begin() const;
        const_iterator end() const;

    private:
        constexpr static inline auto compare = [](const auto& a, const auto& b)
                                               {
                                                   return a.second < b.second;
                                               };
        size_type max_size_;
        data_t data_;
    };

} // namespace core

#include "heap.hxx"

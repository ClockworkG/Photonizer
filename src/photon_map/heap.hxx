#pragma once

#include "heap.hh"

namespace photon
{
    template <typename V>
    DistanceHeap<V>::DistanceHeap(size_type max_size)
        : max_size_{max_size}
        , data_{}
    {
        data_.reserve(max_size_);
    }

    template <typename V>
    void DistanceHeap<V>::insert(const elt_t& elt)
    {
        if (data_.size() >= max_size_)
            data_.pop_back();

        data_.push_back(elt);
        std::push_heap(std::begin(data_), std::end(data_), compare);
    }

    template <typename V>
    void DistanceHeap<V>::insert(elt_t&& elt)
    {
        if (data_.size() >= max_size_)
            data_.pop_back();

        data_.push_back(std::move(elt));
        std::push_heap(std::begin(data_), std::end(data_), compare);
    }

    template <typename V>
    auto DistanceHeap<V>::top() const -> const elt_t&
    {
        if (data_.empty())
            throw std::length_error{"Heap is empty."};

        return data_.front();
    }

    template <typename V>
    DistanceHeap<V>::operator bool() const noexcept
    {
        return !data_.empty();
    }

    template <typename V>
    auto DistanceHeap<V>::begin() const -> const_iterator
    {
        return std::cbegin(data_);
    }

    template <typename V>
    auto DistanceHeap<V>::end() const -> const_iterator
    {
        return std::cend(data_);
    }
} // namespace photon

#pragma once

#include "heap.hh"

namespace core
{
    template <typename V>
    DistanceHeap<V>::DistanceHeap(size_type max_size)
        : max_size_{max_size}
        , data_{}
    {
        data_.reserve(max_size_);
    }

    template <typename V>
    bool DistanceHeap<V>::insert(const elt_t& elt)
    {
        if (data_.size() >= max_size_)
        {
            std::pop_heap(std::begin(data_), std::end(data_), compare);
            data_.back() = elt;
            std::push_heap(std::begin(data_), std::end(data_), compare);
            return false;
        }

        data_.push_back(elt);
        std::push_heap(std::begin(data_), std::end(data_), compare);
        return true;
    }

    template <typename V>
    bool DistanceHeap<V>::insert(elt_t&& elt)
    {
        if (data_.size() >= max_size_)
        {
            std::pop_heap(std::begin(data_), std::end(data_), compare);
            data_.back() = std::move(elt);
            std::push_heap(std::begin(data_), std::end(data_), compare);
            return false;
        }

        data_.push_back(std::move(elt));
        std::push_heap(std::begin(data_), std::end(data_), compare);
        return true;
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
    auto DistanceHeap<V>::size() const noexcept -> size_type
    {
        return data_.size();
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
} // namespace core

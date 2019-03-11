#pragma once

#include "heap.hh"

template <typename T>
void Heap<T>::insert(const T& elt)
{
    data_.push_back(elt);
    std::push_heap(std::begin(data_), std::end(data_));
}

template <typename T>
void Heap<T>::insert(T&& elt)
{
    data_.push_back(std::move(elt));
    std::push_heap(std::begin(data_), std::end(data_));
}

template <typename T>
auto Heap<T>::begin() const -> const_iterator
{
    return std::cbegin(data_);
}

template <typename T>
auto Heap<T>::end() const -> const_iterator
{
    return std::cend(data_);
}

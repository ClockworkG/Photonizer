#pragma once

#include <algorithm>
#include <vector>

template <typename T>
class Heap
{
    using data_t = std::vector<T>;

public:
    using const_iterator = typename data_t::const_iterator;

    Heap() = default;
    ~Heap() = default;
    Heap(const Heap&) = default;
    Heap(Heap&&) = default;
    Heap& operator=(const Heap&) = default;
    Heap& operator=(Heap&&) = default;

    void insert(const T& elt);
    void insert(T&& elt);

    const_iterator begin() const;
    const_iterator end() const;

private:
    std::vector<T> data_;
};

#include "heap.hxx"

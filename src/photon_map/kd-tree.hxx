#pragma once

#include "kd-tree.hh"

namespace photon
{
    template <typename V>
    template <typename Iterator>
    KDTree<V>::KDTree(Iterator begin, Iterator end)
        : root_{nullptr}
    {
        for (auto it = begin; it != end; it++)
            insert(*it);
    }

    template <typename V>
    bool KDTree<V>::empty() const noexcept
    {
        return root_ == nullptr;
    }

    template <typename V>
    auto KDTree<V>::size() const noexcept -> size_type
    {
        return size_;
    }

    template <typename V>
    KDTree<V>::operator bool() const noexcept
    {
        return !empty();
    }

    template <typename V>
    void KDTree<V>::insert(const value_type& value)
    {
        if (empty())
            root_ = std::make_unique<node_t>(value);
        else
            root_->insert(value);
        size_++;
    }

    template <typename V>
    void KDTree<V>::insert(value_type&& value)
    {
        if (empty())
            root_ = std::make_unique<node_t>(std::move(value));
        else
            root_->insert(std::move(value));
        size_++;
    }

    template <typename V>
    std::ostream& operator<<(std::ostream& os, const KDTree<V>& tree)
    {
        os << "digraph {\n"
           << *tree.root_
           << "}";
        return os;
    }
} // namespace photon

#pragma once

#include "kd-node.hh"

namespace photon::detail
{
    template <typename V>
    KDNode<V>::KDNode(const V& v)
            noexcept(std::is_nothrow_copy_constructible_v<V>)
        : value_{v}
    {}

    template <typename V>
    KDNode<V>::KDNode(V&& v)
            noexcept(std::is_nothrow_move_constructible_v<V>)
        : value_{std::move(v)}
    {}

    template <typename V>
    void KDNode<V>::set_left(child_t left)
    {
        left_ = left;
    }

    template <typename V>
    void KDNode<V>::set_right(child_t right)
    {
        right_ = right;
    }
} // namespace photon::detail

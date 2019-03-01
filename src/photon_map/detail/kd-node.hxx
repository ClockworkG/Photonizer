#pragma once

#include "kd-node.hh"

namespace photon::detail
{
    template <typename V>
    KDNode<V>::KDNode(const V& v)
            noexcept(std::is_nothrow_copy_constructible_v<V>)
        : value_{v}
        , left_{nullptr}
        , right_{nullptr}
    {}

    template <typename V>
    KDNode<V>::KDNode(V&& v)
            noexcept(std::is_nothrow_move_constructible_v<V>)
        : value_{std::move(v)}
        , left_{nullptr}
        , right_{nullptr}
    {}
} // namespace photon::detail

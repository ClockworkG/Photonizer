#pragma once

#include "kd-node.hh"

namespace photon::detail
{
    template <typename V>
    KDNode<V>::KDNode(const V& v, index_t index)
            noexcept(std::is_nothrow_copy_constructible_v<V>)
        : value_{v}
        , index_{index}
    {}

    template <typename V>
    KDNode<V>::KDNode(V&& v, index_t index)
            noexcept(std::is_nothrow_move_constructible_v<V>)
        : value_{std::move(v)}
        , index_{index}
    {}

    template <typename V>
    void KDNode<V>::insert(const V& value)
    {
        if (PointComparePolicy<V>::less(value, value_, index_))
        {
            if (left_ == nullptr)
                left_ = std::make_shared<self_t>(
                        value,
                        PointComparePolicy<V>::next(index_)
                );
            else
                left_->insert(value);
        }
        else
        {
            if (right_ == nullptr)
                right_ = std::make_shared<self_t>(
                        value,
                        PointComparePolicy<V>::next(index_)
                );
            else
                right_->insert(value);
        }
    }

    template <typename V>
    void KDNode<V>::insert(V&& value)
    {
        if (PointComparePolicy<V>::less(value, value_, index_))
        {
            if (left_ == nullptr)
                left_ = std::make_shared<self_t>(
                        std::move(value),
                        PointComparePolicy<V>::next(index_)
                );
            else
                left_->insert(std::move(value));
        }
        else
        {
            if (right_ == nullptr)
                right_ = std::make_shared<self_t>(
                        std::move(value),
                        PointComparePolicy<V>::next(index_)
                );
            else
                right_->insert(std::move(value));
        }
    }

    template <typename T>
    std::ostream& operator<<(std::ostream& os, const KDNode<T>& node)
    {
        if (node.left_ == node.right_)
            return os;

        if (node.left_ != nullptr)
        {
            os << '\t'
               << '"' << static_cast<typename point_traits<T>::point_t>(node.value_)
               << '"' << " -> " << '"'
               << static_cast<typename point_traits<T>::point_t>(node.left_->value_)
               << '"' << '\n'
               << *node.left_;
        }


        if (node.right_ != nullptr)
        {
            os << '\t'
               << '"' << static_cast<typename point_traits<T>::point_t>(node.value_)
               << '"' << " -> " << '"'
               << static_cast<typename point_traits<T>::point_t>(node.right_->value_)
               << '"' << '\n'
               << *node.right_;
        }
        return os;
    }

} // namespace photon::detail

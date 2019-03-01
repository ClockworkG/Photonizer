#pragma once

#include <memory>
#include <type_traits>

namespace photon::detail
{
    template <typename ValueType>
    class KDNode
    {
        using self_t = KDNode<ValueType>;

    public:
        using child_t = std::shared_ptr<self_t>;

        /** \name Ctors & dtor
         * \{ */
        KDNode(const ValueType&)
            noexcept(std::is_nothrow_copy_constructible_v<ValueType>);
        KDNode(ValueType&&)
            noexcept(std::is_nothrow_move_constructible_v<ValueType>);
        ~KDNode() = default;
        KDNode(const KDNode&) = default;
        KDNode(KDNode&&) = default;
        KDNode& operator=(const KDNode&) = default;
        KDNode& operator=(KDNode&&) = default;
        KDNode() = delete;
        /** \} */

        /** \name Mutators.
         * \{ */
        void set_left(child_t left);
        void set_right(child_t right);
        /** \} */

    private:
        ValueType value_;
        child_t left_ = nullptr;
        child_t right_ = nullptr;
    };
} // namespace photon::detail

#include "kd-node.hxx"

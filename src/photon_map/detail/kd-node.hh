#pragma once

#include <memory>
#include <ostream>
#include <type_traits>

#include "point-meta.hh"

namespace photon::detail
{
    template <typename ValueType>
    class KDNode
    {
        using self_t = KDNode<ValueType>;
        using point_t = typename point_traits<ValueType>::point_t;
        using index_t = typename point_traits<ValueType>::index_t;

        template <typename T>
        friend std::ostream& operator<<(std::ostream&, const KDNode<T>&);

    public:
        using child_t = std::shared_ptr<self_t>;

        /** \name Ctors & dtor
         * \{ */
        KDNode(const ValueType& value, index_t index = index_t{})
            noexcept(std::is_nothrow_copy_constructible_v<ValueType>);
        KDNode(ValueType&& value, index_t index = index_t{})
            noexcept(std::is_nothrow_move_constructible_v<ValueType>);
        ~KDNode() = default;
        KDNode(const KDNode&) = default;
        KDNode(KDNode&&) = default;
        KDNode& operator=(const KDNode&) = default;
        KDNode& operator=(KDNode&&) = default;
        KDNode() = delete;
        /** \} */

        /** \name Modifiers
         * \{ */
        void insert(const ValueType& value);
        void insert(ValueType&& value);
        /** \} */

    private:
        ValueType value_;
        child_t left_ = nullptr;
        child_t right_ = nullptr;
        index_t index_;
    };
} // namespace photon::detail

#include "kd-node.hxx"

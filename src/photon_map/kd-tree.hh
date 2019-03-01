#pragma once

#include <memory>
#include <ostream>

#include "detail/kd-node.hh"

/// Handles photon tracing and storing.
namespace photon
{
    /// Data structure to partition space and efficiently store photon.
    template <typename ValueType>
    class KDTree
    {
        using self_t = KDTree<ValueType>;

        template <typename T>
        friend std::ostream& operator<<(std::ostream&, const KDTree<T>&);

    public:
        using value_type = ValueType;

        /** \name Ctors & dtor
         * \{ */
        template <typename Iterator>
        KDTree(Iterator begin, Iterator end);
        KDTree() = default;
        ~KDTree() = default;
        KDTree(const KDTree&) = default;
        KDTree(KDTree&&) = default;
        KDTree& operator=(const KDTree&) = default;
        KDTree& operator=(KDTree&&) = default;
        /** \} */

        /** \name Capacity
         * \{ */
        bool empty() const noexcept;
        /** \} */

        /** \name Casts
         * \{ */
        operator bool() const noexcept;
        /** \} */

        /** \name Modifiers
         * \{ */
        void insert(const value_type& value);
        void insert(value_type&& value);
        /** \} */

    private:
        using node_t = detail::KDNode<value_type>;
        using node_ptr_t = std::unique_ptr<node_t>;

        node_ptr_t root_ = nullptr;
    };
} // namespace photon

#include "kd-tree.hxx"

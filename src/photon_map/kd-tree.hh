#pragma once

#include <memory>

#include "detail/kd-node.hh"

/// Handles photon tracing and storing.
namespace photon
{
    /// Data structure to partition space and efficiently store photon.
    template <typename ValueType>
    class KDTree
    {
    public:
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

    private:
        using node_ptr_t = std::unique_ptr<detail::KDNode<ValueType>>;

        node_ptr_t root_ = nullptr;
    };
} // namespace photon

#include "kd-tree.hxx"

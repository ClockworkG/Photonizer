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
        using size_type = std::size_t;

        /** \name Ctors & dtor
         * \{ */
        KDTree() = default;
        ~KDTree() = default;
        KDTree(KDTree&&) = default;
        KDTree& operator=(KDTree&&) = default;
        KDTree(const KDTree&) = delete;
        KDTree& operator=(const KDTree&) = delete;
        /** \} */

        /** \name Capacity
         * \{ */
        bool empty() const noexcept;
        size_type size() const noexcept;
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
        std::size_t size_ = 0;
    };
} // namespace photon

#include "kd-tree.hxx"

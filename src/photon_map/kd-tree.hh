#pragma once

#include <optional>
#include <ostream>
#include <vector>

#include "detail/brown.hh"
#include "heap.hh"

/// Handles photon tracing and storing.
namespace photon
{
    /// Data structure to partition space and efficiently store positions.
    template <typename ValueType>
    class KDTree
    {
    public:
        using value_type = ValueType;
        using size_type = std::size_t;
        using node_t = value_type;
        using point_t = typename point_traits<value_type>::point_t;
        using data_type = std::vector<node_t>;

        /** \name Ctors & dtor
         * \{ */
        template <typename Iterator>
        KDTree(Iterator begin, Iterator end);
        KDTree() = default;
        ~KDTree() = default;
        KDTree(KDTree&&) = default;
        KDTree& operator=(KDTree&&) = default;
        KDTree(const KDTree&) = delete;
        KDTree& operator=(const KDTree&) = delete;
        /** \} */

        /** \name Element access
         * \{ */
        /// Return the underlying vector.
        const data_type& data() const noexcept;
        /** \} */

        /** \name Algorithm
         * \{ */
        Heap<value_type> nearest(const point_t& point) const;
        /** \} */

    private:
        /// Nodes.
        data_type data_;
    };

    template <typename ValueType>
    std::ostream& operator<<(std::ostream&, const KDTree<ValueType>&);

} // namespace photon

#include "kd-tree.hxx"

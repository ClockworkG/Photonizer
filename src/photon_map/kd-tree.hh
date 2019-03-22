#pragma once

#include <optional>
#include <ostream>
#include <vector>

#include "detail/brown.hh"
#include "heap.hh"
#include "math.hh"

/// Handles photon tracing and storing.
namespace photon
{
    /// Data structure to partition space and efficiently store positions.
    template <typename ValueType>
    class KDTree
    {
        using atom_t = typename point_traits<ValueType>::atom_t;

    public:
        using value_type = ValueType;
        using size_type = std::size_t;
        using node_t = value_type;
        using point_t = typename point_traits<value_type>::point_t;
        using data_type = std::vector<node_t>;

        /** \name Ctors & dtor
         * \{ */
        KDTree(size_type size);
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
        data_type& data() noexcept;
        /** \} */

        /** \name Algorithm
         * \{ */
        DistanceHeap<value_type> nearest(const point_t& query,
                                         std::size_t max_count,
                                         atom_t max_dist) const;
        /** \} */

    private:
        bool is_in_tree(std::size_t index) const noexcept;
        void nearest_(const point_t& point,
                      DistanceHeap<value_type>& heap,
                      atom_t& max_dist,
                      std::size_t splitting,
                      std::size_t index = 1) const;

        /// Nodes.
        data_type data_;
    };

    template <typename ValueType>
    std::ostream& operator<<(std::ostream&, const KDTree<ValueType>&);

} // namespace photon

#include "kd-tree.hxx"

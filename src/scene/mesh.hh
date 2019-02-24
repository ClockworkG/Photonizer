#pragma once

#include <list>
#include <vector>

#include "vector3.hh"

namespace scene
{
    class Mesh;

    /// Type to use when manipulating a \a Mesh.
    using mesh_t = const Mesh*;

    namespace detail
    {
        class MeshManager;
    }

    /**
     * \brief Represents a mesh with a list of polygons.
     * \remark This type should not be used directly, use \a mesh_t instead.
     */
    class Mesh
    {
        friend detail::MeshManager;

    public:
        /// A vertex described by a position and a normal.
        using vertex_t = std::pair<Vector3f, Vector3f>;
        /// A polygon defined by some vertices.
        using polygon_t = std::vector<vertex_t>;
        /// All polygons of the mesh.
        using polygons_t = std::list<polygon_t>;
        /** \name Iterating
         * \{ */
        using const_iterator = polygons_t::const_iterator;
        /** \} */

        /** \name Ctors and dtors.
         * \{ */
        Mesh() noexcept = default;
        ~Mesh() = default;
        Mesh(Mesh&&) noexcept = default;
        Mesh& operator=(Mesh&&) noexcept = default;
        /** \} */

        Mesh(const Mesh&) = delete;
        Mesh& operator=(const Mesh&) = delete;

        /** \name Iterating
         * \{ */
        const_iterator begin() const;
        const_iterator end() const;
        /** \} */

        /// Access the polygons of the mesh.
        const polygons_t& polygons() const noexcept;

    private:
        /// Add a polygon to the mesh.
        void add_polygon(const polygon_t& polygon);

        /// List of polygons.
        polygons_t polygons_;
    };
} // namespace scene

#include "mesh.hxx"

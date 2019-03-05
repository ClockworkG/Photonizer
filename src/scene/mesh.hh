#pragma once

#include <filesystem>
#include <list>
#include <vector>

#include "polygon.hh"
#include "vector3.hh"

namespace scene
{
    /// Represents a mesh with a set of polygons.
    class Mesh
    {
    public:
        /// A vertex described by a position and a normal.
        using vertex_t = std::pair<Vector3f, Vector3f>;
        /// A polygon defined by some vertices.
        using polygon_t = Polygon;
        /// All polygons of the mesh.
        using polygons_t = std::list<polygon_t>;
        /** \name Iterating
         * \{ */
        using const_iterator = polygons_t::const_iterator;
        /** \} */

        /** \name Ctors & dtors.
         * \{ */
        Mesh(const std::filesystem::path& filename);
        ~Mesh() = default;
        Mesh(const Mesh&) = delete;
        Mesh(Mesh&&) noexcept = default;
        Mesh& operator=(const Mesh&) = delete;
        Mesh& operator=(Mesh&&) noexcept = default;
        /** \} */

        /** \name Iterating
         * \{ */
        const_iterator begin() const;
        const_iterator end() const;
        /** \} */

    private:
        /// List of polygons.
        polygons_t polygons_;
    };
} // namespace scene

#include "mesh.hxx"

#pragma once

#include <experimental/filesystem>
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
        Mesh(const std::experimental::filesystem::path& filename);
        ~Mesh() = default;
        Mesh(const Mesh&) = delete;
        Mesh(Mesh&&) = default;
        Mesh& operator=(const Mesh&) = delete;
        Mesh& operator=(Mesh&&) = delete;
        /** \} */

        /** \name Iterating
         * \{ */
        const_iterator begin() const;
        const_iterator end() const;
        /** \} */

        const std::string& get_path() const noexcept;

    private:
        /// List of polygons.
        polygons_t polygons_;

        /// Filename associated to the polygon.
        const std::string path_;
    };
} // namespace scene

#include "mesh.hxx"

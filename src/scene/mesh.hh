#pragma once

#include <list>
#include <vector>

#include "vector3.hh"

namespace scene
{
    class Mesh;

    using mesh_t = const Mesh* const;

    class Mesh
    {
        friend class MeshStorage;

    public:
        using vertex_t = std::pair<Vector3f, Vector3f>;
        using polygon_t = std::vector<vertex_t>;
        using polygons_t = std::list<polygon_t>;
        using const_iterator = polygons_t::const_iterator;

        Mesh() noexcept = default;
        ~Mesh() = default;
        Mesh(Mesh&&) noexcept = default;
        Mesh& operator=(Mesh&&) noexcept = default;

        Mesh(const Mesh&) = delete;
        Mesh& operator=(const Mesh&) = delete;

        const_iterator begin() const;
        const_iterator end() const;

        const polygons_t& polygons() const noexcept;

    private:
        void add_polygon(const polygon_t& polygon);

        polygons_t polygons_;
    };
} // namespace scene

#include "mesh.hxx"

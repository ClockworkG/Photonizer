#pragma once

#include "mesh.hh"
#include "object.hh"

namespace scene
{
    class MeshObject : public Object
    {
    public:
        MeshObject(mesh_t mesh) noexcept;
        virtual ~MeshObject() = default;
        MeshObject(const MeshObject&) = delete;
        MeshObject(MeshObject&&) = delete;
        MeshObject& operator=(const MeshObject&) = delete;
        MeshObject& operator=(MeshObject&&) = delete;

        operator bool() const noexcept;

    private:
        [[maybe_unused]]
        mesh_t mesh_;
    };

    inline MeshObject::MeshObject(mesh_t mesh) noexcept
        : mesh_(mesh)
    {}

    inline MeshObject::operator bool() const noexcept
    {
        return mesh_ != nullptr;
    }
} // namespace scene

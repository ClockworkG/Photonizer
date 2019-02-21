#pragma once

#include "mesh.hh"
#include "vector3.hh"

namespace scene
{
    class Object
    {
    public:
        using pos_t = Vector3f;

        Object(const pos_t& position, mesh_t mesh) noexcept;
        ~Object() = default;
        Object(const Object&) = default;
        Object(Object&&) = default;
        Object& operator=(const Object&) = default;
        Object& operator=(Object&&) = default;

    protected:
        pos_t   position_;
        mesh_t  mesh_;
    };

    inline Object::Object(const pos_t& position, mesh_t mesh) noexcept
        : position_(position)
        , mesh_(mesh)
    {}
} // namespace scene

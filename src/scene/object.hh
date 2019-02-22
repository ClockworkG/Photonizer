#pragma once

#include "mesh.hh"
#include "vector3.hh"

namespace scene
{
    /// Object to be rendered.
    class Object
    {
    public:
        /// Position type.
        using pos_t = Vector3f;

        /** \name Ctors and dtors.
         * \{ */
        Object(const pos_t& position, mesh_t mesh) noexcept;
        ~Object() = default;
        Object(const Object&) = default;
        Object(Object&&) = default;
        Object& operator=(const Object&) = default;
        Object& operator=(Object&&) = default;
        /** \} */

        /** \name Getters.
         * \{ */
        mesh_t  get_mesh() const noexcept;
        pos_t   get_position() const noexcept;
        /** \} */

    protected:
        /// Position of the object in the scene.
        pos_t   position_;
        /// Mesh of the object.
        mesh_t  mesh_;
    };

    inline Object::Object(const pos_t& position, mesh_t mesh) noexcept
        : position_(position)
        , mesh_(mesh)
    {}

    inline mesh_t Object::get_mesh() const noexcept
    {
        return mesh_;
    }

    inline Object::pos_t Object::get_position() const noexcept
    {
        return position_;
    }
} // namespace scene

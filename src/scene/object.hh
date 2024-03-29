#pragma once

#include <experimental/filesystem>

#include <boost/flyweight.hpp>
#include <boost/flyweight/key_value.hpp>

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
        Object(const pos_t& position,
               const std::experimental::filesystem::path& mesh_path) noexcept;
        ~Object() = default;
        Object(const Object&) = default;
        Object(Object&&) = default;
        Object& operator=(const Object&) = default;
        Object& operator=(Object&&) = default;
        /** \} */

        /** \name Getters.
         * \{ */
        const Mesh& get_mesh() const noexcept;
        pos_t       get_position() const noexcept;
        /** \} */

    protected:
        struct mesh_name_extractor
        {
            const std::string& operator()(const Mesh& mesh)
            {
                return mesh.get_path();
            }
        };

        using mesh_unique_t =
            boost::flyweight<
                boost::flyweights::key_value<
                    std::string,
                    Mesh>
            >;


        /// Position of the object in the scene.
        pos_t           position_;
        /// Mesh of the object.
        mesh_unique_t   mesh_;
    };
} // namespace scene

#include "object.hxx"

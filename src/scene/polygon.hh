#pragma once

#include <optional>
#include <vector>

#include <boost/flyweight.hpp>
#include <tiny_obj_loader.h>

#include "material.hh"
#include "vector3.hh"

namespace scene
{
    class Polygon : public std::vector<std::pair<Vector3f, Vector3f>>
    {
    public:
        void            set_material(const tinyobj::material_t& mat);
        const Material& get_material() const;

    private:
        using material_unique_t = boost::flyweight<Material>;

        std::optional<material_unique_t> material_ = std::nullopt;
    };

    inline void Polygon::set_material(const tinyobj::material_t& mat)
    {
        material_ = Material
        {
            mat.dissolve,
            mat.shininess,
            Color(mat.ambient[0],  mat.ambient[1],  mat.ambient[2]),
            Color(mat.diffuse[0],  mat.diffuse[1],  mat.diffuse[2]),
            Color(mat.specular[0], mat.specular[1], mat.specular[2])
        };
    }

    inline const Material& Polygon::get_material() const
    {
        return *material_;
    }
} // namespace scene

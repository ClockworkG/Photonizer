#pragma once

#include <optional>
#include <vector>

#include <boost/flyweight.hpp>
#include <boost/flyweight/key_value.hpp>
#include <tiny_obj_loader.h>

#include "material.hh"
#include "rgb.hh"
#include "vector3.hh"

namespace scene
{
    class Polygon : public std::vector<std::pair<Vector3f, Vector3f>>
    {
        using super_t = std::vector<std::pair<Vector3f, Vector3f>>;

    public:
        Polygon();
        Polygon(Material&& mat);
        const Material& get_material() const;

    private:
        struct material_filename_extractor
        {
            const std::string& operator()(const Material& mat)
            {
                return mat.name;
            }
        };

        using material_unique_t =
            boost::flyweight<
                boost::flyweights::key_value<
                    std::string,
                    Material,
                    material_filename_extractor>
            >;

        material_unique_t material_;
    };

    inline
    Polygon::Polygon(Material&& mat)
           : super_t()
           , material_(std::move(mat))
    {}

    inline const Material& Polygon::get_material() const
    {
        return material_.get();
    }
} // namespace scene

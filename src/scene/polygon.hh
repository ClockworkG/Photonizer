#pragma once

#include <vector>

#include <boost/flyweight.hpp>

#include "material.hh"
#include "vector3.hh"

namespace scene
{
    class Polygon : public std::vector<std::pair<Vector3f, Vector3f>>
    {
    private:
        using material_unique_t = boost::flyweight<Material>;

        material_unique_t material_;
    };
} // namespace scene

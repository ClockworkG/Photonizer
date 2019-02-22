#pragma once

#include "mesh.hh"

namespace scene
{
    inline const Mesh::polygons_t& Mesh::polygons() const noexcept
    {
        return polygons_;
    }

    inline Mesh::const_iterator Mesh::begin() const
    {
        return std::cbegin(polygons_);
    }

    inline Mesh::const_iterator Mesh::end() const
    {
        return std::cend(polygons_);
    }

    inline void Mesh::add_polygon(const polygon_t& polygon)
    {
        polygons_.push_back(std::move(polygon));
    }
} // namespace scene

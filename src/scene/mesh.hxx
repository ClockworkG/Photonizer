#pragma once

#include "mesh.hh"

namespace scene
{
    inline Mesh::const_iterator Mesh::begin() const
    {
        return std::cbegin(polygons_);
    }

    inline Mesh::const_iterator Mesh::end() const
    {
        return std::cend(polygons_);
    }

    inline const std::string& Mesh::get_path() const noexcept
    {
        return path_;
    }

} // namespace scene

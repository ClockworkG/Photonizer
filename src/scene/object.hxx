#pragma once

#include "object.hh"

namespace scene
{
    inline
    Object::Object(const pos_t& position, const std::string& mesh_path)
    noexcept
        : position_(position)
        , mesh_{mesh_path}
    {}

    inline const Mesh& Object::get_mesh() const noexcept
    {
        return mesh_.get();
    }

    inline Object::pos_t Object::get_position() const noexcept
    {
        return position_;
    }
} // namespace scene

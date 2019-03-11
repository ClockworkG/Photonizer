#pragma once

#include "material.hh"

namespace scene
{
    inline bool operator==(const Material& lhs, const Material& rhs)
    {
        return (lhs.transparency == rhs.transparency
                && lhs.specular_exponent == rhs.specular_exponent
                && lhs.ambient == rhs.ambient
                && lhs.diffuse == rhs.diffuse
                && lhs.specular == rhs.specular);
    }

    inline std::size_t hash_value(const Material& arg)
    {
        std::size_t hash_v = 0;
        boost::hash_combine(hash_v, arg.name);
        boost::hash_combine(hash_v, arg.transparency);
        boost::hash_combine(hash_v, arg.specular_exponent);
        boost::hash_combine(hash_v, arg.ambient);
        boost::hash_combine(hash_v, arg.diffuse);
        boost::hash_combine(hash_v, arg.specular);
        return hash_v;
    }
} // namespace scene

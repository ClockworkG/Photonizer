#pragma once

#include "color.hh"

namespace scene
{
    struct Material
    {
        Material() = default;
        ~Material() = default;
        Material(const Material&) noexcept = default;
        Material(Material&&) noexcept = default;
        Material& operator=(const Material&) noexcept = default;
        Material& operator=(Material&&) noexcept = default;

        float transparency;
        float specular_exponent;
        Color ambient;
        Color diffuse;
        Color specular;
    };

    bool operator==(const Material& lhs, const Material& rhs);
} // namespace scene

#include "material.hxx"

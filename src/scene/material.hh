#pragma once

#include "rgb.hh"

namespace scene
{
    struct Material
    {
        Material() = default;
        ~Material() = default;
        Material(const Material&) = delete;
        Material(Material&&) noexcept = default;
        Material& operator=(const Material&) = delete;
        Material& operator=(Material&&) noexcept = default;

        float       transparency;
        float       specular_exponent;
        image::RGBN ambient;
        image::RGBN diffuse;
        image::RGBN specular;
    };

    bool operator==(const Material& lhs, const Material& rhs);
} // namespace scene

#include "material.hxx"

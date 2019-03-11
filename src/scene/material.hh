#pragma once

#include "rgb.hh"

namespace scene
{
    struct Material
    {
        Material() = default;
        ~Material() = default;
        Material(const Material&) = delete;
        Material(Material&&) = default;
        Material& operator=(const Material&) = delete;
        Material& operator=(Material&&) = default;

        const std::string name = "default";
        const float       transparency = 0.f;
        const float       specular_exponent = 0.f;
        const image::RGBN ambient = image::RGBN(1.f, 0.f, 1.f);
        const image::RGBN diffuse = image::RGBN(1.f, 0.f, 1.f);
        const image::RGBN specular = image::RGBN(1.f, 0.f, 1.f);
    };

    bool operator==(const Material& lhs, const Material& rhs);
} // namespace scene

#include "material.hxx"

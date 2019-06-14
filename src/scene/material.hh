#pragma once

#include "rgb.hh"

namespace scene
{
    enum class Illum
    {
        COLOR_ON_AMBIENT_OFF = 0,
        COLOR_ON_AMBIENT_ON = 1,
        HIGHLIGHT_ON = 2,
        REFLECTION_ON = 3,
        GLASS_ON = 4,
        FRESNEL_ON = 5,
        REFRACTION_ON_FRESNEL_OFF = 6,
        REFRACTION_ON_FRESNEL_ON = 7,
        REFLECTION_ON_RAY_TRACE_OFF = 8,
        GLASS_ON_RAY_TRACE_OFF = 9,
        CAST_SHADOW = 10
    };

    struct Material
    {
        Material() = default;
        ~Material() = default;
        Material(const Material&) = delete;
        Material(Material&&) = default;
        Material& operator=(const Material&) = delete;
        Material& operator=(Material&&) = delete;

        const std::string name = "default";
        const float       transparency = 1.f;
        const float       specular_exponent = 0.f;
        const float       refraction_index = 1.f;
        const image::RGBN ambient = image::RGBN(1.f, 0.f, 1.f);
        const image::RGBN diffuse = image::RGBN(1.f, 0.f, 1.f);
        const image::RGBN specular = image::RGBN(1.f, 0.f, 1.f);
        const Illum       illum_param = Illum::COLOR_ON_AMBIENT_ON;
    };

    bool operator==(const Material& lhs, const Material& rhs);
} // namespace scene

#include "material.hxx"

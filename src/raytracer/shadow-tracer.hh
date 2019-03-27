#pragma once

#include "ray-caster.hh"

namespace raytracer
{
    class ShadowTracer : public RayCaster<ShadowTracer, image::RGBN>
    {
        using super_t = RayCaster<ShadowTracer, image::RGBN>;
        friend super_t;

    public:
        using value_type = image::RGBN;

        ShadowTracer(scene_ptr_t scene, uint8_t max_depth = 4);
        ~ShadowTracer() = default;
        ShadowTracer(const ShadowTracer&) = default;
        ShadowTracer(ShadowTracer&&) = default;
        ShadowTracer& operator=(const ShadowTracer&) = default;
        ShadowTracer& operator=(ShadowTracer&&) = default;

        float intensity;
        Vector3f normal;
        Vector3f L_v;
        image::RGBN diffuse;
        image::RGBN color;

    private:
        value_type on_hit_impl(const Rayf& ray,
                               const Intersection& isec,
                               uint8_t depth) const;
        value_type on_miss_impl(const Rayf& ray) const;
    };
} // namespace raytracer

#include "shadow-tracer.hh"

namespace raytracer
{
    ShadowTracer::ShadowTracer(scene_ptr_t scene, uint8_t max_depth)
        : super_t(scene, max_depth)
    {}

    auto ShadowTracer::on_hit_impl(const Rayf& ray,
                                   const Intersection& isec,
                                   uint8_t depth) const
        -> value_type
    {
        return image::RGBN(0, 0, 0);
    }

    auto ShadowTracer::on_miss_impl(const Rayf& ray) const
        -> value_type
    {
        float cos_theta = normal * L_v;
        float coef = intensity * cos_theta * albedo;
        coef = clamp(coef, 0.0f, 1.0f);
        return diffuse * color * coef;
    }
} // namespace raytracer

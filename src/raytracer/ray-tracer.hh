#pragma once

#include "ray-caster.hh"
#include "rgb.hh"

namespace raytracer
{
    class RayTracer : public RayCaster<RayTracer, image::RGBN>
    {
        using super_t = RayCaster<RayTracer, image::RGBN>;
        friend super_t;

    public:
        using value_type = image::RGBN;

        RayTracer(scene_ptr_t scene);
        ~RayTracer() = default;
        RayTracer(const RayTracer&) = default;
        RayTracer(RayTracer&&) = default;
        RayTracer& operator=(const RayTracer&) = default;
        RayTracer& operator=(RayTracer&&) = default;

    private:
        value_type on_hit_impl(const Rayf& ray,
                               const Intersection& isec,
                               uint8_t depth) const;
        value_type on_miss_impl(const Rayf& ray) const;

        image::RGBN compute_lights(const Intersection& isec,
                                   const Vector3f& P_v,
                                   const Vector3f& normal) const;

        image::RGBN compute_specular(const Rayf& ray, const Intersection& isec,
                                     const Vector3f& P_v,
                                     const Vector3f& normal,
                                     uint8_t depth) const;

        static Vector3f interpolate_normals(const scene::Polygon& polygon,
                                            float u_bary, float v_bary);
    };
} // namespace raytracer
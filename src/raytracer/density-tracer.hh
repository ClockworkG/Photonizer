#pragma once

#include "photon-map.hh"
#include "ray-caster.hh"
#include "ray-tracer.hh"

namespace raytracer
{
    class DensityTracer : public RayCaster<DensityTracer, float>
    {
        using super_t = RayCaster<DensityTracer, float>;
        friend super_t;

    public:
        using value_type = float;

        DensityTracer(scene_ptr_t scene, const RaytracerConfig& config,
                      photon::PhotonMap&& photon_map);
        ~DensityTracer() = default;
        DensityTracer(const DensityTracer&) = default;
        DensityTracer(DensityTracer&&) = default;
        DensityTracer& operator=(const DensityTracer&) = default;
        DensityTracer& operator=(DensityTracer&&) = default;

    private:
        value_type on_miss_impl(const Rayf& ray) const;
        value_type on_hit_impl(const Rayf& ray,
                               const Intersection& isec,
                               uint8_t depth) const;

        float photon_gathering(const Intersection& isec);

        photon::PhotonMap photon_map_;
        RaytracerConfig config_;
    };
} // namespace raytracer

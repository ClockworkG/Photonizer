#pragma once

#include "photon-map.hh"
#include "ray-caster.hh"
#include "ray-tracer.hh"

namespace raytracer
{
    class DensityTracer : public core::RayCaster<DensityTracer, float>
    {
        using super_t = core::RayCaster<DensityTracer, float>;
        friend super_t;

    public:
        using value_type = float;

        DensityTracer(scene::scene_ptr_t scene, const RaytracerConfig& config,
                      photon::PhotonMap&& photon_map);
        ~DensityTracer() = default;
        DensityTracer(const DensityTracer&) = delete;
        DensityTracer(DensityTracer&&) = default;
        DensityTracer& operator=(const DensityTracer&) = delete;
        DensityTracer& operator=(DensityTracer&&) = delete;

    private:
        value_type on_miss_impl(const Rayf& ray) const;
        value_type on_hit_impl(const Rayf& ray,
                               const core::Intersection& isec,
                               uint8_t depth) const;

        float photon_gathering(const core::Intersection& isec);

        photon::PhotonMap photon_map_;
        RaytracerConfig config_;
    };
} // namespace raytracer

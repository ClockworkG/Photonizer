#include "density-tracer.hh"

namespace raytracer
{
    DensityTracer::DensityTracer(scene_ptr_t scene,
                         const RaytracerConfig& config,
                         photon::PhotonMap&& photon_map)
        : super_t(scene)
        , photon_map_(std::move(photon_map))
        , config_(config)
    {}

    auto
    DensityTracer::on_hit_impl(const Rayf& ray, const Intersection& isec,
                               uint8_t) const
        -> value_type
    {
        Vector3f pos = ray.o + ray.dir * isec.nearest_t;
        return photon_map_.gather(pos,
                                  config_.photon_gathering_radius,
                                  config_.photon_gathering_count).size();
    }

    auto
    DensityTracer::on_miss_impl(const Rayf&) const
        -> value_type
    {
        return 0.f;
    }
} // namespace raytracer

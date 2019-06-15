#pragma once

#include "photon-map.hh"
#include "ray-caster.hh"
#include "rgb.hh"

namespace raytracer
{
    struct RaytracerConfig
    {
        float photon_gathering_radius = 0.5f;
        std::size_t photon_gathering_count = 100;

        int sample_rate = 1;
    };

    class RayTracer : public core::RayCaster<RayTracer, image::RGBN>
    {
        using super_t = core::RayCaster<RayTracer, image::RGBN>;
        friend super_t;

    public:
        using value_type = image::RGBN;

        RayTracer(scene::scene_ptr_t scene, const RaytracerConfig& config);
        RayTracer(scene::scene_ptr_t scene,
                  const RaytracerConfig& config,
                  photon::PhotonMap&& photon_map);
        ~RayTracer() = default;
        RayTracer(const RayTracer&) = delete;
        RayTracer(RayTracer&&) = default;
        RayTracer& operator=(const RayTracer&) = delete;
        RayTracer& operator=(RayTracer&&) = delete;

    private:
        value_type on_hit_impl(const Rayf& ray,
                               const core::Intersection& isec,
                               uint8_t depth) const;
        value_type on_miss_impl(const Rayf& ray) const;

        value_type compute_lights(const Rayf& ray,
                                  const core::Intersection& isec,
                                  const Vector3f& P_v) const;
        value_type compute_refract(const Rayf& ray,
                                   const core::Intersection& isec,
                                   const Vector3f& P_v,
                                   uint8_t depth) const;

        static Vector3f interpolate_normals(const scene::Polygon& polygon,
                                            float u_bary, float v_bary);

        std::optional<photon::PhotonMap> photon_map_ = std::nullopt;
        RaytracerConfig config_;
    };
} // namespace raytracer

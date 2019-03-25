#pragma once

#include <memory>
#include <optional>

#include "scene.hh"
#include "ray.hh"
#include "vector3.hh"

namespace raytracer
{
    using scene_ptr_t = std::shared_ptr<const scene::Scene>;

    struct Intersection
    {
        bool intersected = false;
        float nearest_t = -1;
        float nearest_u_bary = 0.f;
        float nearest_v_bary = 0.f;
        const scene::Polygon* nearest_polygon = nullptr;
        float t = 0.f;
        float u_bary = 0.f;
        float v_bary = 0.f;
    };

    template <typename T, typename ValueType>
    class RayCaster
    {
        friend T;

    public:
        using value_type = ValueType;

        RayCaster(scene_ptr_t scene, uint8_t max_depth = 4);
        ~RayCaster() = default;
        RayCaster(const RayCaster&) = default;
        RayCaster(RayCaster&&) = default;
        RayCaster& operator=(const RayCaster&) = default;
        RayCaster& operator=(RayCaster&&) = default;

        value_type operator()(const Rayf& ray, uint8_t depth = 0) const;

        std::optional<float> get_nearest() const noexcept;
        void set_nearest(std::optional<float> nearest);

    private:
        value_type on_hit(const Rayf& ray,
                          const Intersection& isec,
                          uint8_t depth) const;
        value_type on_miss(const Rayf& ray) const;

        Intersection intersect(const Rayf& ray) const;

        static bool moller_trumbore(const Vector3f& a_v,
                                    const Vector3f& b_v,
                                    const Vector3f& c_v,
                                    const Rayf& ray,
                                    Intersection& isec);

        scene_ptr_t scene_ = nullptr;
        std::optional<float> nearest_ = std::nullopt;
        uint8_t max_depth_ = 4;
    };
} // namespace raytracer

#include "ray-caster.hxx"

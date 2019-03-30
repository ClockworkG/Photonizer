#pragma once

#include <random>

#include "ray-caster.hh"
#include "libphoton.hh"
#include "abstract-light.hh"

namespace photon
{
    class PhotonTracer : public core::RayCaster<PhotonTracer, void>
    {
        using super_t = core::RayCaster<PhotonTracer, void>;
        friend super_t;

    public:
        using photons_t = std::vector<Photon>;

        PhotonTracer(scene::scene_ptr_t scene, uint8_t max_depth);
        ~PhotonTracer() = default;
        PhotonTracer(const PhotonTracer&) = delete;
        PhotonTracer(PhotonTracer&&) = delete;
        PhotonTracer& operator=(const PhotonTracer&) = delete;
        PhotonTracer& operator=(PhotonTracer&&) = delete;

        const photons_t& get_photons() const noexcept;
        Photon& operator[](std::size_t i) const noexcept;
        std::size_t size() const noexcept;

        std::shared_ptr<const scene::AbstractLight> light = nullptr;

        Vector3f randomize_direction() const;

    private:
        void on_miss_impl(const Rayf& ray) const;
        void on_hit_impl(const Rayf& ray,
                         const core::Intersection& isec,
                         uint8_t depth) const;

        mutable std::mt19937 engine_;
        mutable std::uniform_real_distribution<> dist_;
        mutable photons_t photons_;
    };
} // namespace photon

#include "photon-tracer.hxx"

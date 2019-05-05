#pragma once

#include <random>

#include "abstract-photon-tracer.hh"

namespace photon
{
    class PhotonTracer : public AbstractPhotonTracer
    {
        using super_t = AbstractPhotonTracer;
        friend super_t;

    public:
        using photons_t = std::vector<Photon>;

        PhotonTracer(scene::scene_ptr_t scene, uint8_t max_depth);
        ~PhotonTracer() = default;
        PhotonTracer(const PhotonTracer&) = delete;
        PhotonTracer(PhotonTracer&&) = delete;
        PhotonTracer& operator=(const PhotonTracer&) = delete;
        PhotonTracer& operator=(PhotonTracer&&) = delete;

        std::shared_ptr<const scene::AbstractLight> light = nullptr;

        Vector3f init_direction() const;
        Vector3f next_direction() const;
        void handle_photon(Photon&& photon) const;
        void bounce_photon(const Vector3f& hit_point,
                           const core::Intersection& isec,
                           uint8_t depth) const;

    private:
        mutable std::mt19937 engine_;
        mutable std::uniform_real_distribution<> dist_;
    };
} // namespace photon

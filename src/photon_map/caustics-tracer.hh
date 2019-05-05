#pragma once

#include <random>

#include "abstract-photon-tracer.hh"

namespace photon
{
    class CausticsTracer : public AbstractPhotonTracer
    {
        using super_t = AbstractCausticsTracer;
        friend super_t;

    public:
        using photons_t = std::vector<Photon>;

        CausticsTracer(scene::scene_ptr_t scene, uint8_t max_depth);
        ~CausticsTracer() = default;
        CausticsTracer(const CausticsTracer&) = delete;
        CausticsTracer(CausticsTracer&&) = delete;
        CausticsTracer& operator=(const CausticsTracer&) = delete;
        CausticsTracer& operator=(CausticsTracer&&) = delete;

        std::shared_ptr<const scene::AbstractLight> light = nullptr;

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

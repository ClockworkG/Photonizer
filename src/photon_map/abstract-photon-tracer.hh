#pragma once

#include <random>

#include "abstract-light.hh"
#include "libphoton.hh"
#include "ray-caster.hh"

namespace photon
{
    class AbstractPhotonTracer : public core::RayCaster<AbstractPhotonTracer, void>
    {
        using super_t = core::RayCaster<AbstractPhotonTracer, void>;
        friend super_t;

    public:
        using photons_t = std::vector<Photon>;

        AbstractPhotonTracer(scene::scene_ptr_t scene, uint8_t max_depth);
        ~AbstractPhotonTracer() = default;
        AbstractPhotonTracer(const AbstractPhotonTracer&) = delete;
        AbstractPhotonTracer(AbstractPhotonTracer&&) = delete;
        AbstractPhotonTracer& operator=(const AbstractPhotonTracer&) = delete;
        AbstractPhotonTracer& operator=(AbstractPhotonTracer&&) = delete;

        const photons_t& get_photons() const noexcept;
        Photon& operator[](std::size_t i) const noexcept;
        std::size_t size() const noexcept;

        std::shared_ptr<const scene::AbstractLight> light = nullptr;

        Vector3f init_direction() const;
        Vector3f next_direction() const;
        void handle_photon(Photon&& photon) const;
        void bounce_photon(const Vector3f& hit_point,
                           const core::Intersection& isec,
                           uint8_t depth) const;

    private:
        void on_miss_impl(const Rayf& ray) const;
        void on_hit_impl(const Rayf& ray,
                         const core::Intersection& isec,
                         uint8_t depth) const;

    protected:
        mutable photons_t photons_;
    };
} // namespace photon

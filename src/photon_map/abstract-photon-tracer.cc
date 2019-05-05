#include "abstract-photon-tracer.hh"

namespace photon
{
    AbstractPhotonTracer::AbstractPhotonTracer(scene::scene_ptr_t scene, uint8_t max_depth)
        : super_t(scene, max_depth)
        , photons_{}
    {}

    void
    AbstractPhotonTracer::on_miss_impl(const Rayf&) const
    {
        return;
    }

    void
    AbstractPhotonTracer::on_hit_impl(const Rayf& ray,
                                      const core::Intersection& isec,
                                      uint8_t depth) const
    {
        auto hit_point = ray.o + ray.dir * isec.nearest_t;
        auto ph = Photon(hit_point);
        ph.color = light->color * isec.nearest_polygon->get_material().diffuse;
        std::tie(ph.phi, ph.theta) = polar_convert(ray.dir);

        handle_photon(std::move(ph));
        bounce_photon(hit_point, isec, depth);
    }

    auto
    AbstractPhotonTracer::get_photons() const noexcept -> const photons_t&
    {
        return photons_;
    }

    std::size_t AbstractPhotonTracer::size() const noexcept
    {
        return photons_.size();
    }

    Photon& AbstractPhotonTracer::operator[](std::size_t i) const noexcept
    {
        return photons_[i];
    }

    Vector3f AbstractPhotonTracer::init_direction() const
    {
        return Vector3f();
    }

    Vector3f AbstractPhotonTracer::next_direction() const
    {
        return Vector3f();
    }

    void AbstractPhotonTracer::handle_photon(Photon&&) const
    {}

    void AbstractPhotonTracer::bounce_photon(const Vector3f&,
                                             const core::Intersection&,
                                             uint8_t) const
    {}
} // namespace photon

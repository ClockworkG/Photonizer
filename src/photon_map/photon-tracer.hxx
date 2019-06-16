#pragma once

#include "photon-tracer.hh"

namespace photon
{
    PhotonTracer::PhotonTracer(scene::scene_ptr_t scene, uint8_t max_depth)
        : super_t(scene, max_depth)
        , engine_(std::random_device()())
        , dist_(0.f, 1.f)
        , photons_{}
    {}

    inline Vector3f PhotonTracer::randomize_direction() const
    {
        float x = 0;
        float y = 0;
        float z = 0;

        do {
            x = 2 * dist_(engine_) - 1;
            y = 2 * dist_(engine_) - 1;
            z = 2 * dist_(engine_) - 1;
        } while (x * x + y * y + z * z > 1 && y > 0);

        return Vector3f(x, y, z).normalize();
    }

    inline void
    PhotonTracer::on_miss_impl(const Rayf&) const
    {
        return;
    }

    inline void
    PhotonTracer::on_hit_impl(const Rayf& ray,
                              const core::Intersection& isec,
                              uint8_t depth) const
    {
        auto hit_point = ray.o + ray.dir * isec.nearest_t;
        auto ph = Photon(hit_point);
        ph.color = light->color * isec.nearest_polygon->get_material().diffuse;
        std::tie(ph.phi, ph.theta) = polar_convert(ray.dir);

        if (isec.nearest_polygon->get_material().transparency >= 0.95f)
            photons_.push_back(std::move(ph));

        auto transparency = isec.nearest_polygon->get_material().transparency;
        if (transparency > 0.2f)
            return;

        if (dist_(engine_) < 0.8)
        {
            Vector3f nl = isec.normal * ray.dir < 0 ? isec.normal : isec.normal * -1;
            float r1 = 2 * M_PI * dist_(engine_);
            float r2 = dist_(engine_);
            float r2s = std::sqrt(r2);

            Vector3f w = nl;
            Vector3f u = ((std::fabs(w.x) > .1 ? Vector3f(0,1,0) : Vector3f(1,0,0)) ^ w);
            u.normalize();
            Vector3f v = w ^ u;

            Vector3f d = (u * (cosf(r1) * r2s)) + (v * sinf(r1) * r2s) + (w * sqrtf(1 - r2));
            d.normalize();
        }
    }

    inline auto
    PhotonTracer::get_photons() const noexcept -> const photons_t&
    {
        return photons_;
    }

    inline
    std::size_t PhotonTracer::size() const noexcept
    {
        return photons_.size();
    }

    inline
    Photon& PhotonTracer::operator[](std::size_t i) const noexcept
    {
        return photons_[i];
    }
} // namespace photon

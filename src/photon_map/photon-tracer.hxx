#pragma once

#include "photon-tracer.hh"

namespace photon
{
    PhotonTracer::PhotonTracer(raytracer::scene_ptr_t scene, uint8_t max_depth)
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
        } while (x * x + y * y + z * z > 1);

        return Vector3f(x, y, z).normalize();
    }

    inline void
    PhotonTracer::on_miss_impl(const Rayf&) const
    {
        return;
    }

    inline void
    PhotonTracer::on_hit_impl(const Rayf& ray,
                              const raytracer::Intersection& isec,
                              uint8_t depth) const
    {
        auto hit_point = ray.o + ray.dir * isec.nearest_t;
        auto ph = Photon(hit_point);
        ph.color = light->color * isec.nearest_polygon->get_material().diffuse;
        std::tie(ph.phi, ph.theta) = polar_convert(ray.dir);

        photons_.push_back(std::move(ph));

        if (true)
        {
            // FIXME: Not the correct way to bounce a photon
            // The direction should be restricted to the
            // upper hemisphere.
            Ray new_ray(hit_point, randomize_direction());
            (*this)(new_ray, depth + 1);
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

#include "photon-tracer.hh"

namespace photon
{
    CausticsTracer::CausticsTracer(scene::scene_ptr_t scene, uint8_t max_depth)
        : super_t(scene, max_depth)
        , engine_(std::random_device()())
        , dist_(0.f, 1.f)
    {}

    Vector3f CausticsTracer::init_direction() const
    {
        return next_direction();
    }

    Vector3f CausticsTracer::next_direction() const
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

    void CausticsTracer::handle_photon(Photon&& photon) const
    {
        photons_.push_back(std::move(photon));
    }

    void CausticsTracer::bounce_photon(const Vector3f& hit_point,
                                     const core::Intersection&,
                                     uint8_t depth) const
    {
        if (true)
        {
            // FIXME: Not the correct way to bounce a photon
            // The direction should be restricted to the
            // upper hemisphere.
            Ray new_ray(hit_point, next_direction());
            (*this)(new_ray, depth + 1);
        }
    }
}

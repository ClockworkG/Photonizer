#pragma once

#include "photon-map.hh"

namespace photon
{
    inline
    Photon::operator Vector3f() const noexcept
    {
        return position;
    }

    template <typename It>
    PhotonMap::PhotonMap(It begin, It end)
        : tree_(begin, end)
    {}

    inline image::RGBN
    PhotonMap::irradiance_estimate(const Vector3f& position,
                                   const Vector3f&,
                                   float max_dist,
                                   std::size_t max_count) const
    {
        image::RGBN result(0.f, 0.f, 0.f);
        auto nearests = tree_.nearest(position, max_count, max_dist);

        if (nearests.size() < 8)
            return image::RGBN(0.f, 0.f, 0.f);

        for (const auto& [ph, dist] : nearests)
            result += ph.color * static_cast<float>(M_PI);

        result *= static_cast<float>(1.0f / (M_PI * nearests.top().second));

        return result;
    }

    inline
    std::ostream& operator<<(std::ostream& os, const PhotonMap& ph)
    {
        os << ph.tree_;
        return os;
    }
} // namespace photon

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

    inline
    std::ostream& operator<<(std::ostream& os, const PhotonMap& ph)
    {
        os << ph.tree_;
        return os;
    }
} // namespace photon

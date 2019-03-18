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
} // namespace photon

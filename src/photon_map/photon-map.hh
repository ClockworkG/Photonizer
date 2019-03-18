#pragma once

#include "kd-tree.hh"
#include "rgb.hh"
#include "vector3.hh"

namespace photon
{
    struct Photon
    {
        operator Vector3f() const noexcept;

        Vector3f    position;
        image::RGB  color;
        uint8_t     phi;
        uint8_t     theta;
    };

    class PhotonMap
    {
    public:
        template <typename Iterator>
        PhotonMap(Iterator begin, Iterator end);
        PhotonMap() = delete;
        PhotonMap(const PhotonMap&) = delete;
        PhotonMap(PhotonMap&&) = delete;
        PhotonMap& operator=(const PhotonMap&) = delete;
        PhotonMap& operator=(PhotonMap&&) = delete;

    private:
        KDTree<Photon> tree_;
    };
} // namespace photon

#include "photon-map.hxx"

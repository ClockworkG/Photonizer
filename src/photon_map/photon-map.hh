#pragma once

#include <experimental/filesystem>
#include <ostream>
#include <memory>

#include "chrono.hh"
#include "kd-tree.hh"
#include "rgb.hh"
#include "vector3.hh"

namespace photon
{
    struct Photon
    {
        Photon() = default;
        Photon(const Vector3f& pos) : position(pos) {}
        operator Vector3f() const noexcept;

        Vector3f    position;
        image::RGBN color;
        uint8_t     phi;
        uint8_t     theta;
    };

    class PhotonMap
    {
        friend std::ostream& operator<<(std::ostream&, const PhotonMap&);

    public:
        template <typename Iterator>
        PhotonMap(Iterator begin, Iterator end);
        PhotonMap(const std::experimental::filesystem::path& file);
        PhotonMap() = default;
        PhotonMap(const PhotonMap&) = delete;
        PhotonMap(PhotonMap&&) = default;
        PhotonMap& operator=(const PhotonMap&) = delete;
        PhotonMap& operator=(PhotonMap&&) = default;

        void serialize(const std::experimental::filesystem::path& file) const;
        image::RGBN irradiance_estimate(const Vector3f& position,
                                        const Vector3f& normal,
                                        float max_dist,
                                        std::size_t max_count) const;

    private:
        std::unique_ptr<KDTree<Photon>> tree_ = nullptr;
    };
} // namespace photon

#include "photon-map.hxx"

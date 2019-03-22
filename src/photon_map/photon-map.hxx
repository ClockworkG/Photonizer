#pragma once

#include "photon-map.hh"

#include <cstdio>
#include <spdlog/spdlog.h>

namespace photon
{
    inline
    Photon::operator Vector3f() const noexcept
    {
        return position;
    }

    template <typename It>
    PhotonMap::PhotonMap(It begin, It end)
    {
        double elapsed = 0;
        spdlog::info("Balancing KDtree");
        {
            Chrono chrono(elapsed);
            tree_ = std::make_unique<KDTree<Photon>>(begin, end);
        }
        spdlog::info("Balanced tree obtained in {0} ms", elapsed);
    }

    inline
    PhotonMap::PhotonMap(const std::experimental::filesystem::path& file)
    {
        spdlog::info("Loading photons from {0}", file.string());

        auto file_size = std::experimental::filesystem::file_size(file);
        auto count = file_size / sizeof (Photon);
        spdlog::debug("Loading {0} photons", count);
        tree_ = std::make_unique<KDTree<Photon>>(count);

        FILE* raw_file = fopen(file.c_str(), "r");
        fread(tree_->data().data(), count, sizeof (Photon), raw_file);
        fclose(raw_file);
    }

    inline void
    PhotonMap::serialize(const std::experimental::filesystem::path& file) const
    {
        spdlog::info("Saving photon map to {0}", file.string());
        FILE* raw_file = fopen(file.c_str(), "w");
        if (raw_file == NULL)
        {
            spdlog::error("Could not open file {0}", file.string());
            return;
        }

        spdlog::debug("Saving {0} photons", tree_->data().size());
        fwrite(tree_->data().data(), tree_->data().size(),
               sizeof (Photon), raw_file);
        fclose(raw_file);
    }

    inline image::RGBN
    PhotonMap::irradiance_estimate(const Vector3f& position,
                                   const Vector3f&,
                                   float max_dist,
                                   std::size_t max_count) const
    {
        image::RGBN result(0.f, 0.f, 0.f);
        auto nearests = tree_->nearest(position, max_count, max_dist);

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
        os << *ph.tree_;
        return os;
    }
} // namespace photon

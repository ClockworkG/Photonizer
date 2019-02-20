#pragma once

#include <string>
#include <unordered_map>
#include <unordered_set>

#include <gsl/gsl-lite.hpp>

#include "mesh-impl.hh"

namespace scene::detail
{
    class MeshStorage
    {
        using id_t = std::string;
        using filenames_t = std::unordered_set<std::string>;
        using meshes_t = std::unordered_map<id_t, MeshImpl>;

    public:
        using self_ptr_t = gsl::not_null<MeshStorage*>;

        MeshStorage() noexcept = default;
        ~MeshStorage() = default;
        MeshStorage(const MeshStorage&) = delete;
        MeshStorage(MeshStorage&&) = delete;
        MeshStorage& operator=(const MeshStorage&) = delete;
        MeshStorage& operator=(MeshStorage&&) = delete;

        void        load(const id_t& id, const std::string& filename);
        MeshImpl*   get(const id_t& id);

        static self_ptr_t get_instance() noexcept;

    private:
        filenames_t loaded_;
        meshes_t    meshes_;
    };

    inline MeshStorage::self_ptr_t MeshStorage::get_instance() noexcept
    {
        static MeshStorage storage{};
        return &storage;
    }

} // namespace scene::detail

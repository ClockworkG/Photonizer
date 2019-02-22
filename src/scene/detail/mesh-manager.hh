#pragma once

#include <string>
#include <unordered_map>
#include <unordered_set>

#include <gsl/gsl-lite.hpp>

#include "mesh.hh"

namespace scene::detail
{
    class MeshManager
    {
        using id_t = std::string;
        using filenames_t = std::unordered_set<std::string>;
        using meshes_t = std::unordered_map<id_t, Mesh>;

    public:
        using self_ptr_t = gsl::not_null<MeshManager*>;

        MeshManager() noexcept = default;
        ~MeshManager() = default;
        MeshManager(const MeshManager&) = delete;
        MeshManager(MeshManager&&) = delete;
        MeshManager& operator=(const MeshManager&) = delete;
        MeshManager& operator=(MeshManager&&) = delete;

        void        load(const id_t& id, const std::string& filename);
        mesh_t      get(const id_t& id);

        static self_ptr_t get_instance() noexcept;

    private:
        filenames_t loaded_;
        meshes_t    meshes_;
    };

    inline MeshManager::self_ptr_t MeshManager::get_instance() noexcept
    {
        static MeshManager storage{};
        return &storage;
    }
} // namespace scene::detail

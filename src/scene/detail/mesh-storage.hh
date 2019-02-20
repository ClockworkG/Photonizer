#pragma once

#include <string>
#include <unordered_map>
#include <unordered_set>

#include "mesh-impl.hh"

namespace scene::detail
{
    class MeshStorage
    {
        using id_t = std::string;
        using filenames_t = std::unordered_set<std::string>;
        using meshes_t = std::unordered_map<id_t, MeshImpl>;

    public:
        MeshStorage() = default;
        ~MeshStorage() = default;
        MeshStorage(const MeshStorage&) = delete;
        MeshStorage(MeshStorage&&) = delete;
        MeshStorage& operator=(const MeshStorage&) = delete;
        MeshStorage& operator=(MeshStorage&&) = delete;

        void        load(const id_t& id, const std::string& filename);
        MeshImpl*   get(const id_t& id);

        static MeshStorage* get_instance();

    private:
        filenames_t loaded_;
        meshes_t    meshes_;
    };
} // namespace scene::detail

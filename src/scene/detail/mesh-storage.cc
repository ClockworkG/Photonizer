#include "mesh-storage.hh"

namespace scene::detail
{
    MeshStorage* MeshStorage::get_instance()
    {
        static MeshStorage storage{};
        return &storage;
    }

    void MeshStorage::load(const std::string& id, const std::string& filename)
    {
        auto [it, inserted] = loaded_.insert(filename);
        if (!inserted)
            return; // Mesh file has already been loaded.

        meshes_.emplace(std::make_pair(id, MeshImpl{}));

        // Load obj file.
    }

    MeshImpl* MeshStorage::get(const std::string& id)
    {
        auto it = meshes_.find(id);
        if (it == std::cend(meshes_))
            return nullptr;

        return &(it->second);
    }
} // namespace scene::detail

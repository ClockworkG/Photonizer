#include "mesh-manager.hh"

#include <iostream>

#include <tiny_obj_loader.h>

namespace scene::detail
{
    void MeshManager::load(const std::string& id, const std::string& filename)
    {
        auto [it, inserted] = loaded_.insert(filename);
        if (!inserted)
            return; // Mesh file has already been loaded

        meshes_.emplace(std::make_pair(id, Mesh{}));

        {
            tinyobj::attrib_t attrib;
            std::vector<tinyobj::shape_t> shapes;
            std::vector<tinyobj::material_t> materials;

            std::string warn;
            std::string err;
            bool ret = tinyobj::LoadObj(&attrib, &shapes, &materials,
                                        &warn, &err, filename.c_str());
            if (!err.empty())
                std::cerr << err << '\n';

            if (!ret)
                return;

            const auto& shape = shapes[0]; // We assume there is only one shape
            for (int face_idx : shape.mesh.num_face_vertices)
            {
                (void)face_idx;
            }
        }
    }

    mesh_t MeshManager::get(const std::string& id)
    {
        auto it = meshes_.find(id);
        if (it == std::cend(meshes_))
            return nullptr;

        return &(it->second);
    }
} // namespace scene::detail

#include "mesh-manager.hh"

#include <iostream>

#include <tiny_obj_loader.h>

namespace scene::detail
{
    void MeshManager::load(const std::string& id, const std::string& filename)
    {
        {
            auto [it, inserted] = loaded_.insert(filename);
            if (!inserted)
                return; // Mesh file has already been loaded
        }

        auto [it, inserted] = meshes_.emplace(std::make_pair(id, Mesh{}));
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
        std::size_t offset = 0;
        for (std::size_t fv : shape.mesh.num_face_vertices)
        {
            Mesh::polygon_t polygon{};
            for (std::size_t v = 0; v < fv; v++)
            {
                auto idx = shape.mesh.indices[offset + v];
                Vector3f vertex(attrib.vertices[3 * idx.vertex_index + 0],
                                attrib.vertices[3 * idx.vertex_index + 1],
                                attrib.vertices[3 * idx.vertex_index + 2]);
                Vector3f normal(attrib.normals[3 * idx.normal_index + 0],
                                attrib.normals[3 * idx.normal_index + 1],
                                attrib.normals[3 * idx.normal_index + 2]);
                polygon.emplace_back(vertex, normal);
            }
            it->second.add_polygon(polygon);

            offset += fv;
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

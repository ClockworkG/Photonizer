#include "mesh.hh"

#include <iostream>

#include <tiny_obj_loader.h>

namespace scene
{
    Mesh::Mesh(const std::filesystem::path& filename)
        : polygons_{}
    {
        tinyobj::attrib_t attrib;
        std::vector<tinyobj::shape_t> shapes;
        std::vector<tinyobj::material_t> materials;

        std::string warn;
        std::string err;
        bool ret = tinyobj::LoadObj(&attrib, &shapes, &materials,
                                    &warn, &err, filename.c_str(),
                                    filename.parent_path().c_str());
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
            const auto& mat = materials[shape.mesh.material_ids[fv]];
            polygon.set_material(mat);

            polygons_.push_back(polygon);

            offset += fv;
        }
    }
} // namespace scene

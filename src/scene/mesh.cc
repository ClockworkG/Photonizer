#include "mesh.hh"

#include <iostream>
#include <sstream>

#include <tiny_obj_loader.h>
#include <spdlog/spdlog.h>

namespace scene
{
    Mesh::Mesh(const std::experimental::filesystem::path& filename)
        : polygons_{}
        , path_{filename.string()}
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
            spdlog::warn("objloader: {0}", err);

        if (!ret)
            return;

        const auto& shape = shapes[0]; // We assume there is only one shape
        std::size_t offset = 0;
        std::stringstream oss;
        std::size_t face_index = 0;
        for (std::size_t fv : shape.mesh.num_face_vertices)
        {
            const auto material_id = shape.mesh.material_ids[face_index];
            const auto* mat = (material_id != -1 && material_id < static_cast<int>(materials.size())) ?
                                &materials[material_id] :
                                nullptr;

            if (mat != nullptr)
                oss << mat->name << '_' << static_cast<const void*>(mat);

            Mesh::polygon_t polygon(
                    (mat == nullptr) ?
                    Material() :
                    Material
                    {
                        oss.str(),
                        mat->dissolve,
                        mat->shininess,
                        mat->ior,
                        image::RGBN(mat->ambient[0], mat->ambient[1], mat->ambient[2]),
                        image::RGBN(mat->diffuse[0], mat->diffuse[1], mat->diffuse[2]),
                        image::RGBN(mat->specular[0], mat->specular[1], mat->specular[2]),
                        static_cast<Illum>(mat->illum)
                    }
            );

            oss.clear();

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

            polygons_.push_back(polygon);

            offset += fv;
            face_index++;
        }
    }
} // namespace scene

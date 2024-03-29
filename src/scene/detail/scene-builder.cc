#include "scene-builder.hh"

#include <cstdlib>
#include <experimental/filesystem>
#include <iostream>
#include <map>
#include <string>

#include <spdlog/spdlog.h>

#include "light-factory.hh"

namespace ptree = boost::property_tree;

namespace scene::detail
{
    namespace
    {
        template <typename Compound>
        Compound compound_from_ptree(const boost::property_tree::ptree& pt)
        {
            Compound result{};
            std::size_t index = 0;
            for ([[maybe_unused]] const auto& [key, value] : pt)
                result[index++] = value.template get<float>("");

            return result;
        }
    }

    SceneBuilder::SceneBuilder()
        : product_{std::make_shared<Scene>()}
    {}

    void SceneBuilder::set_toplevel(const ptree::ptree& pt)
    {
        product_->name_ = pt.get<std::string>("name");
        product_->width_ = pt.get<Scene::width_t>("width");
        product_->height_ = pt.get<Scene::height_t>("height");
    }

    void SceneBuilder::set_camera(const ptree::ptree& pt)
    {
        Camera c{};
        c.position = compound_from_ptree<Vector3f>(pt.get_child("position"));
        c.forward = compound_from_ptree<Vector3f>(pt.get_child("forward"));
        c.up = compound_from_ptree<Vector3f>(pt.get_child("up"));
        c.fov_x = pt.get<float>("fov_x");
        c.fov_y = pt.get<float>("fov_y");
        c.z_min = pt.get<float>("z_min");

        product_->camera_ = c;
    }

    void SceneBuilder::set_objects(const ptree::ptree& pt)
    {
        auto raw_meshes_base_path = getenv("PHOTONIZER_RESOURCES");
        std::experimental::filesystem::path meshes_base_path{};

        if (raw_meshes_base_path != NULL)
            meshes_base_path = std::experimental::filesystem::path{raw_meshes_base_path};
        else
            meshes_base_path = std::experimental::filesystem::current_path();

        for (const auto& [key, value] : pt)
        {
            auto position = compound_from_ptree<Vector3f>(value.get_child("position"));
            auto mesh_path = std::experimental::filesystem::path(
                value.get<std::string>("mesh")
            );
            if (mesh_path.is_relative())
                mesh_path = meshes_base_path / mesh_path;

            product_->objects_.emplace_back(position, mesh_path.string());
        }
    }

    void SceneBuilder::set_lights(const ptree::ptree& pt)
    {
        LightFactory factory{};

        for (const auto& [key, value] : pt)
        {
            factory.intensity = value.get<float>("intensity");
            factory.color = compound_from_ptree<image::RGB>(value.get_child("color"));
            auto kind = value.get<std::string>("kind");

            if (kind == "point")
            {
                auto position = compound_from_ptree<Vector3f>(value.get_child("position"));
                product_->lights_.push_back(factory.make<PointLight>(position));
            }
            else if (kind == "directional")
            {
                auto direction = compound_from_ptree<Vector3f>(value.get_child("direction"));
                product_->lights_.push_back(factory.make<DirectionalLight>(direction));
            }
            else if (kind == "ambient")
            {
                product_->lights_.push_back(factory.make<AmbientLight>());
            }
            else
            {
                spdlog::warn("Unknown light kind: {0}", kind);
                continue;
            }
        }
    }

} // namespace scene::detail

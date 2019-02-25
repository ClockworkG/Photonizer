#include "scene-builder.hh"

#include <map>
#include <string>

namespace ptree = boost::property_tree;

namespace scene::detail
{
    namespace
    {
        Vector3f vector_from_ptree(const boost::property_tree::ptree& pt)
        {
            Vector3f result{};
            std::size_t index = 0;
            for ([[maybe_unused]] const auto& [key, value] : pt)
                result[index++] = value.get<float>("");

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
        auto pos = vector_from_ptree(pt.get_child("position"));
        auto fwd = vector_from_ptree(pt.get_child("forward"));
        auto up = vector_from_ptree(pt.get_child("up"));
        auto fov = pt.get<float>("fov");

        product_->camera_ = Camera(pos, fwd, up, fov);
    }

    void SceneBuilder::set_objects(const ptree::ptree& pt)
    {
        for (const auto& [key, value] : pt)
        {
            auto position = vector_from_ptree(value.get_child("position"));
            auto mesh_path = value.get<std::string>("mesh");
            product_->objects_.emplace_back(position, mesh_path);
        }
    }

    void SceneBuilder::set_lights(const ptree::ptree& pt)
    {
        (void)pt;
    }

} // namespace scene::detail

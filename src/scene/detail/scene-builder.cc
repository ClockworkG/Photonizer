#include "scene-builder.hh"

#include <map>
#include <string>

#include "object-factory.hh"

namespace ptree = boost::property_tree;

namespace scene::detail
{
    SceneBuilder::SceneBuilder()
        : product_(std::make_shared<Scene>())
    {}

    void SceneBuilder::set_toplevel(const ptree::ptree& pt)
    {
        product_->name_ = pt.get<std::string>("name");
        product_->width_ = pt.get<Scene::width_t>("width");
        product_->height_ = pt.get<Scene::height_t>("height");
    }

    void SceneBuilder::set_camera(const ptree::ptree& pt)
    {
        (void)pt;
    }

    void SceneBuilder::set_objects(const ptree::ptree& pt)
    {
        ObjectFactory factory{};

        for (const auto& [key, value] : pt)
        {
            const auto type = value.get<std::string>("type");
            product_->objects_.push_back(factory(type, value));
        }
    }

    void SceneBuilder::set_lights(const ptree::ptree& pt)
    {
        (void)pt;
    }

} // namespace scene::detail

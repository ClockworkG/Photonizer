#include "scene-builder.hh"

#include <string>

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
        (void)pt;
    }

} // namespace scene::detail

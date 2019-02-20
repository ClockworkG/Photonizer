#pragma once

#include <boost/property_tree/ptree.hpp>

#include "scene.hh"

namespace scene::detail
{
    class SceneBuilder
    {
    public:
        using product_t = std::shared_ptr<Scene>;

        SceneBuilder();
        ~SceneBuilder() = default;

        void        set_toplevel(const boost::property_tree::ptree& pt);
        void        set_camera(const boost::property_tree::ptree& pt);
        void        set_objects(const boost::property_tree::ptree& pt);
        void        set_lights(const boost::property_tree::ptree& pt);
        product_t   product() noexcept;

    private:
        product_t product_;
    };

    inline SceneBuilder::product_t SceneBuilder::product() noexcept
    {
        return product_;
    }

} // namespace scene::detail

#include "libscene.hh"

#include <iostream>

#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>

#include "detail/scene-builder.hh"

namespace ptree = boost::property_tree;

namespace scene
{
    std::shared_ptr<const Scene> load_scene(const std::string& filename)
    {
        detail::SceneBuilder builder{};
        ptree::ptree scene_tree{};

        try {
            ptree::read_json(filename, scene_tree);
        }
        catch (const ptree::json_parser::json_parser_error& err)
        {
            std::cerr << "Syntax error: " << err.what() << '\n';
            return nullptr;
        }

        try {
            builder.set_toplevel(scene_tree);
            builder.set_camera(scene_tree.get_child("camera"));
            builder.set_objects(scene_tree.get_child("objects"));
        }
        catch (const ptree::ptree_bad_path& err)
        {
            std::cerr << "Ill-formed scene file: " << err.what() << '\n';
            return nullptr;
        }

        return builder.product();
    }
} // namespace scene

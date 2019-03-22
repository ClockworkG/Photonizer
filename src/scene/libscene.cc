#include "libscene.hh"

#include <iostream>
#include <chrono>

#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <spdlog/spdlog.h>

#include "chrono.hh"
#include "detail/scene-builder.hh"

namespace ptree = boost::property_tree;

namespace scene
{
    std::shared_ptr<const Scene> load_scene(const std::string& filename)
    {
        spdlog::info("Loading scene {0}", filename);
        detail::SceneBuilder builder{};
        double elapsed = 0;

        try {
            Chrono chrono(elapsed);
            ptree::ptree scene_tree{};
            ptree::read_json(filename, scene_tree);

            builder.set_toplevel(scene_tree);
            builder.set_camera(scene_tree.get_child("camera"));
            builder.set_objects(scene_tree.get_child("objects"));
            builder.set_lights(scene_tree.get_child("lights"));
        }
        catch (const ptree::ptree_bad_path& err)
        {
            spdlog::error("Ill-formed scene file: {0}", err.what());
            return nullptr;
        }
        catch (const ptree::json_parser::json_parser_error& err)
        {
            spdlog::error("Syntax error: {0}", err.what());
            return nullptr;
        }

        spdlog::info("Finished scene loading in {0} ms", elapsed);
        return builder.product();
    }
} // namespace scene

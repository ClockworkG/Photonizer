#pragma once

#include <string>
#include <memory>

#include "scene.hh"

/// Parsing the scene and its objects, delivering a \a Scene.
namespace scene
{
    /**
     * \example scene-usage.cc
     * An example of scene loading and browsing through the scene library.
     */

    /**
     * \brief Load a scene from a file.
     * \param filename The path of the file containing the scene.
     * \return Shared pointer to the \a Scene object created from the file.
     */
    std::shared_ptr<const Scene> load_scene(const std::string& filename);
} // namespace scene

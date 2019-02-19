#pragma once

#include <string>
#include <memory>

#include "scene.hh"

namespace scene
{
    /**
     * \brief Load a scene from a file.
     * \param filename The path of the file containing the scene.
     * \return Shared pointer to the Scene object created from the file.
     */
    std::shared_ptr<const Scene> load_scene(const std::string& filename);

} // namespace scene

#pragma once

#include <memory>
#include <string>
#include <vector>

#include "camera.hh"
#include "object.hh"

namespace scene
{
    namespace detail
    {
        class SceneBuilder;
    } // namespace detail

    class Scene
    {
        friend detail::SceneBuilder;

        using width_t = unsigned short;
        using height_t = unsigned short;
        using objects_t = std::vector<std::unique_ptr<Object>>;

    public:
        Scene() = default;
        ~Scene() = default;

        Scene(const Scene&) = delete;
        Scene(Scene&&) = delete;
        Scene& operator=(const Scene&) = delete;
        Scene& operator=(Scene&&) = delete;

    private:
        width_t     width_ = 0;
        height_t    height_ = 0;
        std::string name_;
        Camera      camera_;
        objects_t   objects_;
    };
} // namespace scene

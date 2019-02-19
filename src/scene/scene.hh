#pragma once

#include <string>

#include "camera.hh"

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
    };
} // namespace scene

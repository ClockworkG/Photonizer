#pragma once

#include <memory>
#include <string>
#include <vector>

#include <gsl/gsl-lite.hpp>

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
        using objects_t = std::vector<Object>;

    public:
        using const_iterator = objects_t::const_iterator;

        Scene() = default;
        ~Scene() = default;

        Scene(const Scene&) = delete;
        Scene(Scene&&) = delete;
        Scene& operator=(const Scene&) = delete;
        Scene& operator=(Scene&&) = delete;

        const_iterator begin() const;
        const_iterator end() const;

    private:
        width_t     width_ = 0;
        height_t    height_ = 0;
        std::string name_;
        objects_t   objects_;
        Camera      cam_;
    };

    inline Scene::const_iterator Scene::begin() const
    {
        return std::cbegin(objects_);
    }

    inline Scene::const_iterator Scene::end() const
    {
        return std::cend(objects_);
    }
} // namespace scene

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

    /// Describes a scene to be rendered.
    class Scene
    {
        friend detail::SceneBuilder;

        using width_t = unsigned short;
        using height_t = unsigned short;
        using objects_t = std::vector<Object>;

    public:
        /** \name Iterating
         * \{ */
        using const_iterator = objects_t::const_iterator;
        /** \} */

        /** \name Ctors and dtors.
         * \{ */
        Scene() = default;
        ~Scene() = default;
        Scene(const Scene&) = default;
        Scene(Scene&&) = default;
        Scene& operator=(const Scene&) = default;
        Scene& operator=(Scene&&) = default;
        /** \} */

        /** \name Iterating
         * \{ */
        const_iterator begin() const;
        const_iterator end() const;
        /** \} */

        /// Access the camera of the scene.
        const Camera& get_camera() const noexcept;

    private:
        /// Screen width.
        width_t     width_ = 0;
        /// Screen width.
        height_t    height_ = 0;
        /// Name of the scene.
        std::string name_;
        /// All the objects in the scene.
        objects_t   objects_;
        /// Camera used to render.
        Camera      camera_;
    };

    inline Scene::const_iterator Scene::begin() const
    {
        return std::cbegin(objects_);
    }

    inline Scene::const_iterator Scene::end() const
    {
        return std::cend(objects_);
    }

    inline const Camera& Scene::get_camera() const noexcept
    {
        return camera_;
    }
} // namespace scene

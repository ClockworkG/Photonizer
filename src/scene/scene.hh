#pragma once

#include <memory>
#include <string>
#include <vector>

#include <gsl/gsl-lite.hpp>

#include "abstract-light.hh"
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
        using objects_t = std::list<Object>;
        using light_ptr_t = std::shared_ptr<AbstractLight>;
        using lights_t = std::list<light_ptr_t>;

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

        /// Access the width of the scene.
        const width_t& get_width() const noexcept;
        /// Access the height of the scene.
        const height_t& get_height() const noexcept;
        /// Access lights in the scene.
        const lights_t& lights() const noexcept;
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
        /// All lights in the scene.
        lights_t    lights_;
        /// Camera used to render.
        Camera      camera_;
    };

    using scene_ptr_t = std::shared_ptr<const Scene>;

    inline Scene::const_iterator Scene::begin() const
    {
        return std::cbegin(objects_);
    }

    inline Scene::const_iterator Scene::end() const
    {
        return std::cend(objects_);
    }

    inline const Scene::width_t& Scene::get_width() const noexcept
    {
        return width_;
    }

    inline const Scene::height_t& Scene::get_height() const noexcept
    {
        return height_;
    }

   inline auto Scene::lights() const noexcept -> const lights_t&
    {
        return lights_;
    }

    inline const Camera& Scene::get_camera() const noexcept
    {
        return camera_;
    }
} // namespace scene

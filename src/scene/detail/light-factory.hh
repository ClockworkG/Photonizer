#pragma once

#include <memory>

#include "abstract-light.hh"
#include "ambient-light.hh"
#include "point-light.hh"
#include "directional-light.hh"
#include "rgb.hh"
#include "vector3.hh"

namespace scene::detail
{
    struct LightFactory
    {
    public:
        using product_t = std::shared_ptr<AbstractLight>;

        /** \name Ctors & dtor.
         * \{ */
        LightFactory() = default;
        ~LightFactory() = default;
        LightFactory(const LightFactory&) = delete;
        LightFactory(LightFactory&&) = delete;
        LightFactory& operator=(const LightFactory&) = delete;
        LightFactory& operator=(LightFactory&&) = delete;
        /** \} */

        template <typename LightKind, typename ... Args>
        product_t make(Args&&... args);

        image::RGB  color;
        float       intensity;
    };
} // namespace scene::detail

#include "light-factory.hxx"

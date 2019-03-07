#pragma once

#include <memory>

#include "abstract-light.hh"
#include "color.hh"
#include "point-light.hh"
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

        product_t operator()();

        Color color;
        Vector3f position;
    };
} // namespace scene::detail

#include "light-factory.hxx"

#pragma once

#include "light-factory.hh"

namespace scene::detail
{
    auto LightFactory::operator()() -> product_t
    {
        return std::make_shared<PointLight>(position, color);
    }
} // namespace scene::detail

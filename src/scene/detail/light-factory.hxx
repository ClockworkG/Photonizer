#pragma once

#include "light-factory.hh"

namespace scene::detail
{
    template <typename LightKind, typename ... Args>
    auto LightFactory::make(Args&&... args) -> product_t
    {
        return std::make_shared<LightKind>(
                color, intensity,
                std::forward<Args>(args)...
        );
    }
} // namespace scene::detail

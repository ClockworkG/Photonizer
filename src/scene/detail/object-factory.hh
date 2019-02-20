#pragma once

#include <memory>

#include "object.hh"

namespace scene::detail
{
    class ObjectFactory
    {
    public:
        using object_ptr_t = std::unique_ptr<Object>;

        ObjectFactory() = default;
        ~ObjectFactory() = default;
        ObjectFactory(const ObjectFactory&) = delete;
        ObjectFactory(ObjectFactory&&) = delete;
        ObjectFactory& operator=(const ObjectFactory&) = delete;
        ObjectFactory& operator=(ObjectFactory&&) = delete;

        // FIXME: add factory methods
        // object_ptr_t operator()(Position p, float radius) const;
        object_ptr_t operator()() const
        {
            return std::make_unique<Object>();
        }
    };
} // namespace scene::detail

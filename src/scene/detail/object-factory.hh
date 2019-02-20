#pragma once

#include <memory>
#include <string>

#include <boost/property_tree/ptree.hpp>

#include "object.hh"

namespace scene::detail
{
    class ObjectFactory
    {
    public:
        using object_ptr_t = std::unique_ptr<Object>;
        using type_t = std::string;

        ObjectFactory() = default;
        ~ObjectFactory() = default;
        ObjectFactory(const ObjectFactory&) = delete;
        ObjectFactory(ObjectFactory&&) = delete;
        ObjectFactory& operator=(const ObjectFactory&) = delete;
        ObjectFactory& operator=(ObjectFactory&&) = delete;

        object_ptr_t operator()(const type_t& type,
                                const boost::property_tree::ptree& pt) const;
    };
} // namespace scene::detail

#pragma once

#include "object.h"

namespace scene
{
    class Sphere : public Object
    {
    public:
        Sphere() = default;
        virtual ~Sphere() = default;
        Sphere(const Sphere&) = delete;
        Sphere(Sphere&&) = delete;
        Sphere& operator=(const Sphere&) = delete;
        Sphere& operator=(Sphere&&) = delete;

        // FIXME: intersection
    public:
        // FIXME: position, radius
    };
} // namespace scene

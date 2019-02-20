#pragma once

#include "object.hh"
#include "vector3.hh"

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
    private:
        Vector3f position;
    };
} // namespace scene

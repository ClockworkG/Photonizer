#pragma once

namespace scene
{
    class Object
    {
    public:
        Object() = default;
        virtual ~Object() = default;
        Object(const Object&) = delete;
        Object(Object&&) = delete;
        Object& operator=(const Object&) = delete;
        Object& operator=(Object&&) = delete;

        // FIXME: intersection
    };
} // namespace scene

#include <gtest/gtest.h>

#include "kd-tree.hh"
#include "vector3.hh"

using namespace photon;

struct DummyPhoton
{
    explicit DummyPhoton(const Vector3f& v) : vect{v} {}
    DummyPhoton() = default;
    DummyPhoton(const DummyPhoton&) = default;
    DummyPhoton(DummyPhoton&&) = default;

    operator Vector3f() const noexcept
    {
        return vect;
    }

    Vector3f vect;
};

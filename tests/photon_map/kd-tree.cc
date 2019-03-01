#include <gtest/gtest.h>

#include "kd-tree.hh"
#include "vector3.hh"

using namespace photon;

struct Dummy
{
    Dummy() = default;
    Dummy(const Dummy& d) { d.copied = true; }
    Dummy(Dummy&& d) { d.moved = true; }
    mutable bool moved = false;
    mutable bool copied = false;

    explicit operator Vector3f() const noexcept
    {
        return Vector3f{};
    }
};

struct DummyPhoton
{
    explicit DummyPhoton(const Vector3f& v) : vect{v} {}
    DummyPhoton() = default;
    DummyPhoton(const DummyPhoton&) = default;
    DummyPhoton(DummyPhoton&&) = default;

    explicit operator Vector3f() const noexcept
    {
        return vect;
    }

    Vector3f vect;
};

TEST(KDTree, DefaultCtor)
{
    KDTree<Dummy> tree{};
    EXPECT_TRUE(tree.empty());
}

TEST(KDTree, InsertEmpty)
{
    KDTree<Dummy> tree{};

    tree.insert(Dummy{});

    EXPECT_FALSE(tree.empty());
}

TEST(KDTree, InsertLeft)
{
    KDTree<DummyPhoton> tree{};
    tree.insert(DummyPhoton{Vector3f{}});

    tree.insert(DummyPhoton{Vector3f{-1, 0}});
}

TEST(KDTree, InsertRight)
{
}

TEST(KDNode, ValueCopyCtor)
{
    Dummy d{};
    detail::KDNode node{d};
    EXPECT_TRUE(d.copied);
}

TEST(KDNode, ValueMoveCtor)
{
    Dummy d{};
    detail::KDNode node{std::move(d)};
    EXPECT_TRUE(d.moved);
}

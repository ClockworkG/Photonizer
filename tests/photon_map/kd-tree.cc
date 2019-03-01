#include <gtest/gtest.h>

#include "kd-tree.hh"

using namespace photon;

struct Dummy
{
    Dummy() = default;
    Dummy(const Dummy& d) { d.copied = true; }
    Dummy(Dummy&& d) { d.moved = true; }
    mutable bool moved = false;
    mutable bool copied = false;
};

TEST(KDTree, DefaultCtor)
{
    KDTree<Dummy> tree{};
    EXPECT_TRUE(tree.empty());
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

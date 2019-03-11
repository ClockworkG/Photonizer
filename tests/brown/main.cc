#include <algorithm>
#include <iostream>
#include <iomanip>
#include <vector3.hh>

#include "kd-tree.hh"

namespace ph = photon;

struct Photon
{
    Photon(const Vector3f& v) : vect{v} {}
    Photon() = default;
    Photon(const Photon&) = default;
    Photon(Photon&&) = default;
    Photon& operator=(const Photon&) = default;

    operator Vector3f() const noexcept
    {
        return vect;
    }

    Vector3f vect;
};

int main()
{
    std::vector<Photon> points{};
    for (std::size_t i = 0; i < 100; i++)
    {
        points.emplace_back(Vector3f{static_cast<float>(std::rand() % 500 - 500),
                                     static_cast<float>(std::rand() % 500 - 500),
                                     static_cast<float>(std::rand() % 500 - 500)});
    }

    [[maybe_unused]]
    auto tree = ph::KDTree<Photon>(points.begin(), points.end());
    std::cout << tree;
}

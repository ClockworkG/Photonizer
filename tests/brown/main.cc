#include <algorithm>
#include <iostream>
#include <iomanip>
#include <vector3.hh>
#include "detail/brown.hh"
#include "detail/point-comparator.hh"

namespace ph = photon::detail;

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
    std::vector points =
    {
        Vector3f{2, 3, 3},
        Vector3f{5, 4, 2},
        Vector3f{9, 6, 7},
        Vector3f{4, 7, 9},
        Vector3f{8, 1, 5},
        Vector3f{7, 2, 6},
        Vector3f{9, 4, 1},
        Vector3f{8, 4, 2},
        Vector3f{9, 7, 8},
        Vector3f{6, 3, 1},
        Vector3f{3, 4, 5},
        Vector3f{1, 6, 8},
        Vector3f{9, 5, 3},
        Vector3f{2, 1, 3},
        Vector3f{8, 7, 6}
    };

    std::vector indexes{0, 1, 2};
    auto comp = ph::PointComparator<Photon>(indexes.begin(), indexes.end());
    std::sort(points.begin(), points.end(), comp);
    for (const auto& vec : points)
        std::cout << vec << '\n';

//    auto tree = ph::make_balanced_tree<Photon>(points.begin(), points.end());
}

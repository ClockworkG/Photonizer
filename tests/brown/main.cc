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
    std::vector points =
    {
        Photon{Vector3f{2, 3, 3}},
       Photon{Vector3f{5, 4, 2}},
       Photon{Vector3f{9, 6, 7}},
       Photon{Vector3f{4, 7, 9}},
       Photon{Vector3f{8, 1, 5}},
       Photon{Vector3f{7, 2, 6}},
       Photon{Vector3f{9, 4, 1}},
       Photon{Vector3f{8, 4, 2}},
       Photon{Vector3f{9, 7, 8}},
       Photon{Vector3f{6, 3, 1}},
       Photon{Vector3f{3, 4, 5}},
       Photon{Vector3f{1, 6, 8}},
       Photon{Vector3f{9, 5, 3}},
       Photon{Vector3f{2, 1, 3}},
       Photon{Vector3f{8, 7, 6}}
    };

    [[maybe_unused]]
    auto tree = ph::KDTree<Photon>(points.begin(), points.end());
    const auto& data = tree.data();
    std::cout << "digraph {\n";
    for (std::size_t i = 0; i < data.size(); i++)
    {
        std::size_t next = 2 * i;

        if (next < data.size())
        {
            std::cout << '"' << static_cast<Vector3f>(*data[i]) << '"'
                      << " -> "
                      << '"' << static_cast<Vector3f>(*data[next]) << '"'
                      << '\n';

            if (next + 1 < data.size())
            {
                std::cout << '"' << static_cast<Vector3f>(*data[i]) << '"'
                          << " -> "
                          << '"' << static_cast<Vector3f>(*data[next + 1]) << '"'
                          << '\n';

            }
        }
    }
    std::cout << "}\n";
}

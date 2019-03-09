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
    for (std::size_t i = 0; i < 10000; i++)
    {
        points.emplace_back(Vector3f{static_cast<float>(std::rand() % 500 - 500),
                                     static_cast<float>(std::rand() % 500 - 500),
                                     static_cast<float>(std::rand() % 500 - 500)});
    }

    [[maybe_unused]]
    auto tree = ph::KDTree<Photon>(points.begin(), points.end());
    const auto& data = tree.data();
    std::cout << "digraph {\n";
    for (std::size_t i = 0; i < data.size(); i++)
    {
        std::size_t next = 2 * i;

        if (next < data.size() && data[next])
        {
            std::cout << '"' << static_cast<Vector3f>(*data[i]) << '"'
                      << " -> "
                      << '"' << static_cast<Vector3f>(*data[next]) << '"'
                      << '\n';

            if (next + 1 < data.size() && data[next + 1])
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

#include "scene/libscene.hh"

int main()
{
    // `scene` is an `std::shared_ptr<const scene::Scene>`
    auto the_scene = scene::load_scene("my_scene.json");

    // These loops should be used in the ray casting loop in order to
    // find the intersection with the casted ray.
    for (const auto& obj : the_scene)
    {
        // `obj` is a `const scene::Object&`.
        for (const auto& polygon : obj.get_mesh())
        {
            // `polygon` is a `scene::Mesh::polygon_t`.
            // Each polygon can have three or more vertices.
            for (const auto& [vertex, normal] : polygon)
            {
                // Iterating over very vertices of the polygon.
                // ...
            }
        }
    }
}

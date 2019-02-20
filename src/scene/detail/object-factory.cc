#include "object-factory.hh"

#include "mesh.hh"
#include "mesh-object.hh"
#include "mesh-storage.hh"
#include "sphere.hh"

namespace ptree = boost::property_tree;

namespace scene::detail
{
    namespace
    {
        using callback_t =
            std::function<ObjectFactory::object_ptr_t(const ptree::ptree& pt)>;

        static inline std::map<std::string, callback_t> callbacks =
        {
            {
                "mesh",
                [](auto pt)
                {
                    auto mesh_name = pt.template get<std::string>("mesh");
                    auto mesh = MeshStorage::get_instance()->get(mesh_name);
                    return std::make_unique<MeshObject>(mesh);
                }
            },
            {
                "sphere",
                [](auto)
                {
                    return std::make_unique<Sphere>();
                }
            }
        };
    }

    ObjectFactory::object_ptr_t
    ObjectFactory::operator()(const type_t& type, const ptree::ptree& pt) const
    {
        return callbacks[type](pt);
    }
} // namespace scene::detail

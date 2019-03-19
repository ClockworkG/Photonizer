#include "ray-tracer.hh"

#include "ambient-light.hh"
#include "directional-light.hh"
#include "point-light.hh"
#include "shadow-tracer.hh"

namespace raytracer
{
    RayTracer::RayTracer(scene_ptr_t scene)
        : super_t(scene)
    {}

    auto
    RayTracer::on_hit_impl(const Rayf& ray, const Intersection& isec,
                           uint8_t depth) const
        -> value_type
    {
        image::RGBN color = image::RGBN(0, 0, 0);
        const auto normal = interpolate_normals(*isec.nearest_polygon,
                                                isec.nearest_u_bary,
                                                isec.nearest_v_bary);

        Vector3f P_v = ray.o + (ray.dir * isec.nearest_t);

        color += compute_lights(isec, P_v, normal);
        color += compute_specular(ray, isec, P_v, normal, depth);

        return color;
    }

    auto
    RayTracer::compute_specular(const Rayf& ray, const Intersection& isec,
                                const Vector3f& P_v, const Vector3f& normal,
                                uint8_t depth) const
        -> image::RGBN
    {
        image::RGBN color = image::RGBN(0, 0, 0);

        const auto& material = isec.nearest_polygon->get_material();

        const Vector3f R_v = ray.dir - (normal * (ray.dir * normal)) * 2;
        float bias = 0.0001f; // to avoid self intersection
        Ray specular_ray = Ray(P_v + normal * bias, R_v);
        color += material.specular * (*this)(specular_ray, depth + 1);

        return color;
    }

    auto
    RayTracer::compute_lights(const Intersection& isec, const Vector3f& P_v,
                              const Vector3f& normal) const
        -> image::RGBN
    {
        image::RGBN color = image::RGBN(0, 0, 0);

        const auto& material = isec.nearest_polygon->get_material();
        // FIXME: should come from material

        Vector3f L_v;
        float intensity;

        ShadowTracer tracer(scene_, max_depth_);

        tracer.normal = normal;
        tracer.albedo = 0.18f / M_PI;

        // foreach light
        for (auto it = scene_->lights().begin(); it != scene_->lights().end(); ++it)
        {
            Intersection shadow_isec;
            auto& light = *(*it);
            if (const auto *ambient_light = dynamic_cast<scene::AmbientLight*>(&light))
            {
                color += ambient_light->color * material.ambient * ambient_light->intensity;
                continue;
            }
            if (const auto *dir_light = dynamic_cast<scene::DirectionalLight*>(&light))
            {
                L_v = Vector3f(-dir_light->direction.x,
                               -dir_light->direction.y,
                               -dir_light->direction.z);
                L_v.normalize();
                intensity = dir_light->intensity;
            }
            else if (const auto *point_light = dynamic_cast<scene::PointLight*>(&light))
            {
                L_v = point_light->position - P_v; // direction of light, but reversed
                float r2 = L_v.norm();
                shadow_isec.nearest_t = std::sqrt(r2); // we search obstacles between P and light
                L_v.normalize();
                // square falloff
                intensity = point_light->intensity / (4 * M_PI * r2);
            }

            // shadow test
            tracer.intensity = intensity;
            tracer.L_v = L_v;
            tracer.color = light.color;
            tracer.diffuse = material.diffuse;

            const float bias = 0.0001f; // to avoid self intersection
            const Ray light_ray = Ray(P_v + normal * bias, L_v);

            color += tracer(light_ray);
        }
        return color;
    }

    auto
    RayTracer::on_miss_impl(const Rayf& ray) const
        -> value_type
    {
        return image::RGBN(0.f, 0.f, 0.f);
    }

    Vector3f RayTracer::interpolate_normals(const scene::Polygon& polygon,
                                            float u_bary, float v_bary)
    {
        const auto& n0 = polygon[0].second;
        const auto& n1 = polygon[1].second;
        const auto& n2 = polygon[2].second;

        return n0 * (1.0f - u_bary - v_bary) + n1 * u_bary + n2 * v_bary;
    }
} // namespace raytracer
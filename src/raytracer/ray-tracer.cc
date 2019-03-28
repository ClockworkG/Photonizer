#include "ray-tracer.hh"

#include "ambient-light.hh"
#include "directional-light.hh"
#include "point-light.hh"

#include <algorithm>

namespace raytracer
{
    constexpr static inline auto BIAS = 0.0001f; // to avoid self intersection

    RayTracer::RayTracer(scene_ptr_t scene,
                         const RaytracerConfig& config)
        : super_t(scene)
        , photon_map_(std::nullopt)
        , config_(config)
    {}

    RayTracer::RayTracer(scene_ptr_t scene,
                         const RaytracerConfig& config,
                         photon::PhotonMap&& photon_map)
        : super_t(scene)
        , photon_map_(std::move(photon_map))
        , config_(config)
    {}

    auto
    RayTracer::on_hit_impl(const Rayf& ray, const Intersection& isec,
                           uint8_t depth) const
        -> value_type
    {
        image::RGBN color = image::RGBN(0, 0, 0);

        const auto& material = isec.nearest_polygon->get_material();
        // intersection point
        Vector3f P_v = ray.o + (ray.dir * isec.nearest_t);

        // FIXME: use the illum parameter from MTL file
        if (material.transparency != 0)
            color += compute_lights(ray, isec, P_v) * material.transparency;
        if (material.transparency != 1)
            color += compute_refract(ray, isec, P_v, depth) * (1 - material.transparency);
        // FIXME: allow reflection without transparency

        color += photon_map_->irradiance_estimate(
                P_v,
                isec.normal,
                config_.photon_gathering_radius,
                config_.photon_gathering_count
        ) * 11.f;

        return color;
    }

    static inline
    Vector3f reflect_dir(const Vector3f& ray_dir, const Vector3f& normal)
    {
        return ray_dir - (normal * (ray_dir * normal)) * 2;
    }

    static inline
    Vector3f refract_dir(const Rayf& ray, const Vector3f& normal, float ior)
    {
        float cos_incident = clamp(ray.dir * normal, -1.f, 1.f);
        float eta1 = 1; // FIXME
        float eta2 = ior;
        Vector3f normal_copy = normal;
        if (cos_incident < 0) // if we're entering the material (from outside to inside)
            cos_incident = -cos_incident;
        else
        {
            std::swap(eta1, eta2);
            normal_copy = Vector3f(-normal.x, -normal.y, -normal.z);
        }
        float eta = eta1 / eta2;
        float k = 1 - eta * eta * (1 - cos_incident * cos_incident);
        if (k < 0)
            return Vector3f(0, 0, 0);
        else
            return ray.dir * eta + normal_copy * (eta * cos_incident - std::sqrt(k));
    }

    static inline
    float fresnel(const Rayf& ray, const Vector3f& normal, float ior)
    {
        float cos_incident = clamp(ray.dir *  normal, -1.f, 1.f);
        float eta1 = 1; // FIXME
        float eta2 = ior;
        if (cos_incident > 0) // if we're leaving the material (from inside to outside)
            std::swap(eta1, eta2);
        float sin_transmit = eta1 / eta2 * std::sqrt(std::max(0.f, 1 - cos_incident * cos_incident));
        if (sin_transmit >= 1) // total internal reflection
            return 1;

        float cos_transmit = std::sqrt(std::max(0.f, 1 - sin_transmit * sin_transmit));
        cos_incident = std::abs(cos_incident);
        float Rs = ((eta2 * cos_incident) - (eta1 * cos_transmit)) / ((eta2 * cos_incident) + (eta1 * cos_transmit));
        float Rp = ((eta1 * cos_transmit) - (eta2 * cos_transmit)) / ((eta1 * cos_incident) + (eta2 * cos_transmit));
        return (Rs * Rs + Rp * Rp) / 2;
    }

    auto RayTracer::compute_refract(const Rayf& ray,
                                    const Intersection& isec,
                                    const Vector3f& P_v,
                                    uint8_t depth) const
        -> value_type
    {
        float ior = isec.nearest_polygon->get_material().refraction_index;
        float reflect_coef = fresnel(ray, isec.normal, ior);
        bool from_outside = (ray.dir * isec.normal) < 0;
        Vector3f biased_normal = isec.normal * BIAS;

        image::RGBN refract_color = image::RGBN(0, 0, 0);
        if (reflect_coef < 1)
        {
            Rayf refract_ray;
            refract_ray.dir = (refract_dir(ray, isec.normal, ior)).normalize();
            refract_ray.o = from_outside ? P_v - biased_normal : P_v + biased_normal;

            refract_color = (*this)(refract_ray, depth + 1);
        }

        Rayf reflect_ray;
        reflect_ray.dir = (reflect_dir(ray.dir, isec.normal)).normalize();
        reflect_ray.o = from_outside ? P_v + biased_normal : P_v - biased_normal;
        image::RGBN reflect_color = (*this)(reflect_ray, depth + 1);

        return reflect_color * reflect_coef + refract_color * (1.f - reflect_coef);
    }

    auto
    RayTracer::compute_lights(const Rayf& ray,
                              const Intersection& isec,
                              const Vector3f& P_v)
        const -> value_type
    {
        image::RGBN color = image::RGBN(0, 0, 0);
        const auto& material = isec.nearest_polygon->get_material();

        Vector3f L_v;
        float intensity;

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
                L_v = dir_light->direction.inverse();
                L_v.normalize();
                intensity = dir_light->intensity;
            }
            else if (const auto *point_light = dynamic_cast<scene::PointLight*>(&light))
            {
                L_v = point_light->position - P_v; // direction of light, but reversed
                float r2 = L_v.norm();
                L_v.x /= r2, L_v.y /= r2, L_v.z /= r2; // normalize
                shadow_isec.nearest_t = std::sqrt(r2); // we search obstacles between P and light
                // square falloff
                intensity = point_light->intensity / (4 * M_PI * r2);
            }

            // shadow test
            const Ray light_ray = Ray(P_v + isec.normal * BIAS, L_v);
            intersect(light_ray, shadow_isec);
            // FIXME: could be optimized to not test all the objects after the first intersection
            if (!shadow_isec.intersected)
            {
                // Diffuse
                float cos_theta = isec.normal * L_v;
                float diffuse_coef = intensity * cos_theta;
                diffuse_coef = clamp(diffuse_coef, 0.f, 1.f);
                color += material.diffuse * light.color * diffuse_coef;

                // Specular
                Vector3f R = reflect_dir(L_v.inverse(), isec.normal);
                float specular_coef = R * (ray.dir.inverse());
                specular_coef = std::pow(std::max(0.f, specular_coef),
                                         material.specular_exponent);
                color += material.specular * intensity * specular_coef;
            }
        }
        return color;
    }

    auto
    RayTracer::on_miss_impl(const Rayf&) const
        -> value_type
    {
        return image::RGBN(0.f, 0.f, 0.f);
    }

} // namespace raytracer

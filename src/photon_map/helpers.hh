/*
 * This file should disappear when ray casting becomes generic.
 */
#pragma once

#include "ray.hh"
#include "scene.hh"
#include "vector3.hh"

namespace photon
{
    image::RGBN ray_cast(const scene::Scene& scene, const Rayf& ray, const uint8_t& depth);

    struct Intersection
    {
        bool intersected = false;
        float nearest_t = -1;
        float nearest_u_bary;
        float nearest_v_bary;
        const scene::Polygon *nearest_polygon;
        float t;
        float u_bary;
        float v_bary;
    };

    bool moller_trumbore(const Vector3f& a_v, const Vector3f& b_v, const Vector3f& c_v,
                         const Rayf& ray, Intersection& isec)
    {
        Vector3f ab_v = b_v - a_v;
        Vector3f ac_v = c_v - a_v;
        Vector3f p_v = ray.dir ^ ac_v;
        const float det = ab_v * p_v;

        if (std::abs(det) < epsilon) // if ray and surface are parallel
            return false;

        float inv_det = 1.0 / det;
        Vector3f t_v = ray.o - a_v;
        isec.u_bary = t_v * p_v * inv_det;
        if (isec.u_bary < 0.0 || isec.u_bary > 1.0)
            return false;

        Vector3f q_v = t_v ^ ab_v;
        isec.v_bary = ray.dir * q_v * inv_det;
        if (isec.v_bary < 0.0 || isec.u_bary + isec.v_bary > 1.0)
            return false;

        isec.t = ac_v * q_v * inv_det;
        return true;
    }

    Vector3f interpolate_normals(const scene::Polygon& polygon,
                                  const float& u_bary, const float& v_bary)
    {
        const auto& n0 = polygon[0].second;
        const auto& n1 = polygon[1].second;
        const auto& n2 = polygon[2].second;

        return n0 * (1.0f - u_bary - v_bary) + n1 * u_bary + n2 * v_bary;
    }

    void intersect(const scene::Scene& scene, const Rayf& ray, Intersection& isec)
    {
        for (const auto& object : scene)
        {
            // FIXME: check bounding volume

            for (const auto& polygon : object.get_mesh())
            {
                // Compute triangle vertexes position in scene
                const Vector3f a_v = polygon[0].first + object.get_position();
                const Vector3f b_v = polygon[1].first + object.get_position();
                const Vector3f c_v = polygon[2].first + object.get_position();

                if (moller_trumbore(a_v, b_v, c_v, ray, isec)
                    && isec.t >= 0
                    && (isec.nearest_t == -1 || isec.t < isec.nearest_t))
                {
                    // save values of intersection as the nearest
                    isec.intersected = true;
                    isec.nearest_t = isec.t;
                    isec.nearest_u_bary = isec.u_bary;
                    isec.nearest_v_bary = isec.v_bary;
                    isec.nearest_polygon = &polygon;
                }
            }
        }
    }
}

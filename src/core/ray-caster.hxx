#pragma once

namespace core
{
    constexpr static inline auto epsilon = 0.0000001f;
    template <typename T, typename V>
    inline
    RayCaster<T, V>::RayCaster(scene_ptr_t scene, uint8_t max_depth)
        : scene_(scene)
        , max_depth_(max_depth)
    {}

    template <typename T, typename V>
    inline auto
    RayCaster<T, V>::operator()(const Rayf& ray, uint8_t depth) const
        -> value_type
    {
        if (depth > max_depth_)
            return on_miss(ray);

        Intersection isec;
        intersect(ray, isec, false);
        if (isec.intersected)
            return on_hit(ray, isec, depth);

        return on_miss(ray);
    }

    template <typename T, typename V>
    inline auto
    RayCaster<T, V>::on_hit(const Rayf& ray, const Intersection& isec,
                            uint8_t depth) const
        -> value_type
    {
        return static_cast<const T*>(this)->on_hit_impl(ray, isec, depth);
    }

    template <typename T, typename V>
    inline auto
    RayCaster<T, V>::on_miss(const Rayf& ray) const
        -> value_type
    {
        return static_cast<const T*>(this)->on_miss_impl(ray);
    }

    template <typename T, typename V>
    inline
    void RayCaster<T, V>::intersect(const Rayf& ray, Intersection& isec,
                                    bool shadow_test) const
    {
        for (const auto& object : *scene_)
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
                if (shadow_test && isec.nearest_polygon != nullptr)
                    break;
            }
            if (shadow_test && isec.nearest_polygon != nullptr)
                break;
        }

        if (isec.nearest_polygon != nullptr)
        {
            isec.normal = interpolate_normals(*isec.nearest_polygon,
                                              isec.nearest_u_bary,
                                              isec.nearest_v_bary);
        }
    }

    template <typename T, typename V>
    bool RayCaster<T, V>::moller_trumbore(const Vector3f& a_v,
                                          const Vector3f& b_v,
                                          const Vector3f& c_v,
                                          const Rayf& ray,
                                          Intersection& isec)
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


    template <typename T, typename V>
    inline auto
    RayCaster<T, V>::interpolate_normals(const scene::Polygon& polygon,
                                         float u_bary, float v_bary)
        -> Vector3f
    {
        const auto& n0 = polygon[0].second;
        const auto& n1 = polygon[1].second;
        const auto& n2 = polygon[2].second;

        return n0 * (1.f - u_bary - v_bary) + n1 * u_bary + n2 * v_bary;
    }

} // namespace core

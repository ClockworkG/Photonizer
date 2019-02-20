#pragma once

namespace scene
{
    class MeshImpl
    {
    public:
        MeshImpl() = default;
        ~MeshImpl() = default;
        MeshImpl(MeshImpl&&) = default;

        MeshImpl(const MeshImpl&) = delete;
        MeshImpl& operator=(const MeshImpl&) = delete;
        MeshImpl& operator=(MeshImpl&&) = delete;
    };
} // namespace scene

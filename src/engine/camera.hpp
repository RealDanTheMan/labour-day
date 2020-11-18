#ifndef CAMERA_HPP_
#define CAMERA_HPP_

#include "transform.hpp"
#include <memory>

namespace Engine
{
    class Camera
    {
        private:
        Transform m_transform;
        Mat4 m_proj;
        float m_near;
        float m_far;
        float m_fov;
        float m_aspect;

        public:
        Camera();
        Camera(const uint32_t w, const uint32_t h, const float fov, const float aspect);
        Camera(const Camera &rhs);
        static std::unique_ptr<Camera> Create(const uint32_t w, const uint32_t h, const float fov);

        const Mat4 View() const;
        const Mat4 &Projection() const;
        Transform& GetTransform();

        void RecomputePerspective();

    };
}

#endif
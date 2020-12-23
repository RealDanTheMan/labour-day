#ifndef CAMERA_HPP_
#define CAMERA_HPP_

#include "transform.hpp"
#include <memory>

namespace Engine
{
    class 
    Camera
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
        Camera(const float fov, const float aspect);
        Camera(const uint32_t w, const uint32_t h, const float fov);
        Camera(const Camera &rhs);
        static std::unique_ptr<Camera> Create(const float fov, const float aspect);

        void SetTransform(const Transform &tr);
        void SetNearClip(const float val);
        void SetFarClip(const float val);
        void SetFOV(const float val);
        void SetAspect(const float val);
        
        const float GetNearClip() const;
        const float GetFarClip() const;
        const float GetFOV() const;
        const float GetAspect() const;

        const Mat4 View() const;
        const Mat4 &Projection() const;
        Transform& GetTransform();

        void RecomputePerspective();

    };
}

#endif
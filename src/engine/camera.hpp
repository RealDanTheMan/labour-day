#ifndef CAMERA_HPP_
#define CAMERA_HPP_

#include "transform.hpp"

namespace Engine
{
    class Camera
    {
        private:
        Transform m_transform;
        Transform m_proj;
        float m_near;
        float m_far;

        public:
        Camera();
        Camera(const Camera &rhs);

        const Mat4 &View() const;
        const Mat4 &Projection() const;
        Transform& GetTransform();

    };
}

#endif
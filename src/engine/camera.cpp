#include "camera.hpp"

using namespace Engine;


Camera::Camera():
m_transform(Transform()),
m_proj(Transform()),
m_near(0.001),
m_far(1000000.0f)
{

}

Camera::Camera(const Camera &rhs):
m_transform(rhs.m_transform),
m_proj(rhs.m_proj),
m_near(rhs.m_near),
m_far(rhs.m_far)
{

}


const Mat4& Camera::View() const
{
    return m_transform.Matrix();
}

const Mat4& Camera::Projection() const
{
    return m_proj.Matrix();
}

Transform& Camera::GetTransform()
{
    return m_transform;
}
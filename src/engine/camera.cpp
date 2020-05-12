#include "camera.hpp"
#include "glm/gtx/transform.hpp"

using namespace Engine;


Camera::Camera():
m_transform(Transform()),
m_proj(Transform::IdentityMatrix()),
m_near(0.001),
m_far(1000000.0f),
m_fov(90.0f),
m_aspect(1.0f)
{
    RecomputePerspective();
}

Camera::Camera(const uint32_t w, const uint32_t h, const float fov, const float aspect):
m_transform(Transform()),
m_proj(Transform::IdentityMatrix()),
m_near(0.001),
m_far(1000000.0f),
m_fov(fov),
m_aspect((float)w / (float)h)
{
    RecomputePerspective();
}

Camera::Camera(const Camera &rhs):
m_transform(rhs.m_transform),
m_proj(rhs.m_proj),
m_near(rhs.m_near),
m_far(rhs.m_far)
{
    RecomputePerspective();
}

const Mat4 Camera::View() const
{
    return glm::lookAt(Vec3(m_transform.Translation()), Vec3(0.0, 0.0, 0.0), Vec3(0.0, 1.0, 0.0));
}

const Mat4& Camera::Projection() const
{
    return m_proj;
}

Transform& Camera::GetTransform()
{
    return m_transform;
}

void Camera::RecomputePerspective()
{
    m_proj = glm::perspective(glm::radians(m_fov), m_aspect, m_near, m_far);
}
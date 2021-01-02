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

Camera::Camera(const float fov, const float aspect):
m_transform(Transform()),
m_proj(Transform::IdentityMatrix()),
m_near(0.001),
m_far(1000000.0f),
m_fov(fov),
m_aspect(aspect)
{
    RecomputePerspective();
}

Camera::Camera(const uint32_t w, const uint32_t h, const float fov):
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
m_far(rhs.m_far),
m_fov(rhs.m_fov),
m_aspect(rhs.m_aspect)
{
    RecomputePerspective();
}

const Mat4 Camera::View() const
{
    // World up axis is alwas Y
    const Vec3 up = Vec3(0,1,0);

    // Forward / lookat axis is Z
    const Vec3 forward = m_transform.Matrix()[2];

    // Compute view / lookat matrix
    const Vec3 eye = m_transform.Translation();
    const Vec3 target = eye + (10.0f * forward);
    return glm::lookAt(eye, target, up);
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

void Camera::SetTransform(const Transform &tr)
{
    m_transform.Set(tr);
}

void Camera::SetNearClip(const float val)
{
    m_near = val;
    RecomputePerspective();
}

void Camera::SetFarClip(const float val)
{
    m_far = val;
    RecomputePerspective();
}

void Camera::SetFOV(const float val)
{
    m_fov = val;
    RecomputePerspective();
}

void Camera::SetAspect(const float val)
{
    m_aspect = val;
    RecomputePerspective();
}

const float Camera::GetNearClip() const
{
    return m_near;
}

const float Camera::GetFarClip() const
{
    return m_far;
}

const float Camera::GetFOV() const
{
    return m_fov;
}

const float Camera::GetAspect() const
{
    return m_aspect;
}
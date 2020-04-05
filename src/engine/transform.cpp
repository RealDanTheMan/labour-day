#include "transform.hpp"


using namespace Engine;


Transform::Transform():
m_translation(Transform::IdentityMatrix()),
m_scale(Transform::IdentityMatrix()),
m_rotX(Transform::IdentityMatrix()),
m_rotY(Transform::IdentityMatrix()),
m_rotZ(Transform::IdentityMatrix()),
m_composite(Transform::IdentityMatrix())
{

}

Transform::Transform(const Transform &rhs):
m_translation(rhs.m_translation),
m_scale(rhs.m_scale),
m_rotX(rhs.m_rotX),
m_rotY(rhs.m_rotY),
m_rotZ(rhs.m_rotZ),
m_composite(rhs.m_composite)
{

}

Mat4 Transform::IdentityMatrix()
{
    auto mat = Mat4();

    mat[0] = Vec4(1.0f, 0.0f, 0.0f, 0.0f);
    mat[1] = Vec4(0.0f, 1.0f, 0.0f, 0.0f);
    mat[2] = Vec4(0.0f, 0.0f, 1.0f, 0.0f);
    mat[3] = Vec4(0.0f, 0.0f, 0.0f, 1.0f);

    return mat;
}

void Transform::ComputeMatrix()
{
    Mat4 rot = m_rotX * m_rotY * m_rotZ;
    m_composite = m_scale * rot * m_translation;
}

void Transform::Translate(const Vec3 &translation)
{
    m_translation[3][0] += translation.x;
    m_translation[3][1] += translation.y;
    m_translation[3][2] += translation.z;

    ComputeMatrix();
}

void Transform::Scale(const Vec3 &scale)
{
    m_scale[0][0] *= scale.x;
    m_scale[1][1] *= scale.y;
    m_scale[2][2] *= scale.z;

    ComputeMatrix();
}

void Transform::Scale(const float scale)
{
    m_scale[0][0] *= scale;
    m_scale[1][1] *= scale;
    m_scale[2][2] *= scale;

    ComputeMatrix();
}

const Mat4& Transform::Matrix() const 
{
    return m_composite;
}
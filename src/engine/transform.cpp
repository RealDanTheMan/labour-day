#include "transform.hpp"
#include "glm/gtx/transform.hpp"
#include "glm/gtx/euler_angles.hpp"
#include <glm/gtx/matrix_decompose.hpp> 
#include <glm/gtx/quaternion.hpp>


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
m_composite(rhs.m_composite),
m_changed()
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
    Mat4 rot = m_rotZ * m_rotY * m_rotX;
    m_composite = m_translation * rot * m_scale;
    //m_composite = m_scale * rot * m_translation;

    ChangedEvent().Invoke(666);
}

void Transform::Translate(const Vec3 &translation)
{
    m_translation[3][0] += translation.x;
    m_translation[3][1] += translation.y;
    m_translation[3][2] += translation.z;

    ComputeMatrix();
}

void Transform::SetTranslation(const Vec3 &translation)
{
    m_translation[3][0] = translation.x;
    m_translation[3][1] = translation.y;
    m_translation[3][2] = translation.z;

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

void Transform::SetScale(const Vec3 &scale)
{
    m_scale[0][0] = scale.x;
    m_scale[1][1] = scale.y;
    m_scale[2][2] = scale.z;

    ComputeMatrix();
}

void Transform::SetScale(const float scale)
{
    m_scale[0][0] = scale;
    m_scale[1][1] = scale;
    m_scale[2][2] = scale;

    ComputeMatrix();
}

void Transform::Set(const Transform &tr)
{
    m_translation = tr.m_translation;
    m_rotX = tr.m_rotX;
    m_rotY = tr.m_rotY;
    m_rotZ = tr.m_rotZ;
    m_scale = tr.m_scale;

    ComputeMatrix();
}

void Transform::Reset()
{
    m_translation = Transform::IdentityMatrix();
    m_rotX = Transform::IdentityMatrix();
    m_rotY = Transform::IdentityMatrix();
    m_rotZ = Transform::IdentityMatrix();
    m_scale = Transform::IdentityMatrix();
}

void Transform::TransformBy(const Transform &tr)
{
    const Mat4 res = m_composite * tr.m_composite;

    // TODO: This is a bit pricey to do each time we multiply transforms
    Vec3 pos; Vec3 rot; Vec3 scale;
    Transform::Decompose(res, pos, rot, scale);
    
    SetTranslation(pos);
    SetRotation(rot);
    SetScale(scale);
}

void Transform::TransformByInv(const Transform &tr)
{
    const Mat4 res = m_composite * glm::inverse(tr.m_composite);
    
     // TODO: This is a bit pricey to do each time we multiply transforms
    Vec3 pos; Vec3 rot; Vec3 scale;
    Transform::Decompose(res, pos, rot, scale);
    
    SetTranslation(pos);
    SetRotation(rot);
    SetScale(scale);
}

void Transform::Rotate(const Vec3 &degAngles)
{
    const Vec3 rads = glm::radians(degAngles);

    const Mat4 x = glm::rotate(rads.x, Vec3(1.0, 0.0, 0.0));
    const Mat4 y = glm::rotate(rads.y, Vec3(0.0, 1.0, 0.0));
    const Mat4 z = glm::rotate(rads.z, Vec3(0.0, 0.0, 1.0));

    m_rotX *= x;
    m_rotY *= y;
    m_rotZ *= z;

    ComputeMatrix();
}

void Transform::SetRotation(const Vec3 &degAngles)
{
    const Vec3 rads = glm::radians(degAngles);

    const Mat4 x = glm::rotate(rads.x, Vec3(1.0, 0.0, 0.0));
    const Mat4 y = glm::rotate(rads.y, Vec3(0.0, 1.0, 0.0));
    const Mat4 z = glm::rotate(rads.z, Vec3(0.0, 0.0, 1.0));

    m_rotX = x;
    m_rotY = y;
    m_rotZ = z;

    ComputeMatrix();
}

const Mat4& Transform::Matrix() const 
{
    return m_composite;
}

Vec3 Transform::Translation() const
{
    return Vec3(m_translation[3][0], m_translation[3][1], m_translation[3][2]);
}

Vec3 Transform::Scale() const 
{
    return Vec3(m_scale[0][0], m_scale[1][1], m_scale[2][2]);
}

Vec3 Transform::Rotation() const
{
    const float x = Transform::XAngle(m_rotX);
    const float y = Transform::YAngle(m_rotY);
    const float z = Transform::ZAngle(m_rotZ);

    return glm::degrees(Vec3(x, y, z));
}

Event<ChangedDelegate>& Transform::ChangedEvent()
{
    return m_changed;
}

float Transform::XAngle(const Mat4 &mat)
{
    float x; float y; float z;
    glm::extractEulerAngleXYZ(mat, x, y, z);

    return x;
}

float Transform::YAngle(const Mat4 &mat)
{
    float x; float y; float z;
    glm::extractEulerAngleXYZ(mat, x, y, z);

    return y;
}

float Transform::ZAngle(const Mat4 &mat)
{
    float x; float y; float z;
    glm::extractEulerAngleXYZ(mat, x, y, z);

    return z;
}

void Transform::Decompose(const Mat4 &mat, Vec3 &tr, Vec3 &rot, Vec3 &scale)
{
    glm::quat orientation;
    glm::vec3 skew;
    glm::vec4 perspective;

    glm::decompose(mat, scale, orientation, tr, skew, perspective);
    rot = glm::degrees(glm::eulerAngles(orientation));
}

Mat4 Transform::RotMatrixFromTransform(const Transform &tr)
{
    return tr.m_rotZ * tr.m_rotY * tr.m_rotX;
}
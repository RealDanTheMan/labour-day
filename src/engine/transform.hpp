#ifndef TRANSFORM_HPP_
#define TRANSFORM_HPP_

#include "types.hpp"

namespace Engine
{
    class Transform
    {
        private:
        Mat4 m_composite;
        Mat4 m_translation;
        Mat4 m_scale;
        Mat4 m_rotX;
        Mat4 m_rotY;
        Mat4 m_rotZ;

        public:
        Transform();
        Transform(const Transform &rhs);
        const Mat4& Matrix() const;

        void Translate(const Vec3 &translation);
        void Scale(const Vec3 &scale);
        void Scale(const float scale);
        void Rotate(const Vec3 &degAngles);

        void SetTranslation(const Vec3 &translation);
        void SetScale(const Vec3 &scale);
        void SetScale(const float scale);

        Vec3 Translation() const;
        Vec3 Scale() const;

        static Mat4 IdentityMatrix();

        private:
        void ComputeMatrix();
    };
}

#endif
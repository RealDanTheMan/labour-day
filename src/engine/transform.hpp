#ifndef TRANSFORM_HPP_
#define TRANSFORM_HPP_

#include "types.hpp"
#include "event.hpp"

namespace Engine
{
    using ChangedDelegate = EventDelegate<void, int>;

    class Transform
    {
        private:
        Mat4 m_composite;
        Mat4 m_translation;
        Mat4 m_scale;
        Mat4 m_rotX;
        Mat4 m_rotY;
        Mat4 m_rotZ;

        Event<ChangedDelegate> m_changed;

        public:
        Transform();
        Transform(const Transform &rhs);
        const Mat4& Matrix() const;

        void Translate(const Vec3 &translation);
        void Scale(const Vec3 &scale);
        void Scale(const float scale);
        void Rotate(const Vec3 &degAngles);

        void SetTranslation(const Vec3 &translation);
        void SetRotation(const Vec3 &degAngles);
        void SetScale(const Vec3 &scale);
        void SetScale(const float scale);
        void Set(const Transform &tr);
        void Reset();
        void TransformBy(const Transform &tr);
        void TransformByInv(const Transform &tr);

        Vec3 Translation() const;
        Vec3 Scale() const;
        Vec3 Rotation() const;

        Event<ChangedDelegate>& ChangedEvent();

        static Mat4 IdentityMatrix();
        static float XAngle(const Mat4 &mat);
        static float YAngle(const Mat4 &mat);
        static float ZAngle(const Mat4 &mat);
        static void Decompose(const Mat4 &mat, Vec3 &tr, Vec3 &rot, Vec3 &scale);

        private:
        void ComputeMatrix();
    };
}

#endif
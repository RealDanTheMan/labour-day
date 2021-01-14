#ifndef LIGHTS_HPP_
#define LIGHTS_HPP_

#include "types.hpp"

namespace Engine
{
    class Light
    {
        public:
        enum LightType
        {
            Directional,
            Point,
        };

        Light(LightType type);
        Light(const Light &rhs) = default;
        virtual ~Light();
        LightType GetType() const;

        private:
        LightType m_type;
    };

    class DirectionalLight : public Light
    {
        public:
        DirectionalLight();
        DirectionalLight(const DirectionalLight &rhs) = default;

        const Vec3 & GetDirection() const;
        float GetIntensity() const;

        void SetDirection(const Vec3 &dir);
        void SetIntensity(const float intensity);

        private:
        Vec3 m_dir;
        float m_intensity;
    };
}

#endif
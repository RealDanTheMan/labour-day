#include "lights.hpp"

using namespace Engine;

Light::Light(LightType type):
m_type(type)
{

}

Light::~Light()
{
    
}

Light::LightType Light::GetType() const
{
    return m_type;
}

DirectionalLight::DirectionalLight() : Light(LightType::Directional)
{

}

const Vec3 & DirectionalLight::GetDirection() const
{
    return m_dir;
}

float DirectionalLight::GetIntensity() const
{
    return m_intensity;
}

void DirectionalLight::SetDirection(const Vec3 &dir)
{
    m_dir = dir;
}

void DirectionalLight::SetIntensity(const float intensity)
{
    m_intensity = intensity;
}
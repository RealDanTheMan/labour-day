#include "lightcomponent.hpp"
#include <glm/gtx/rotate_vector.hpp>

using namespace Engine::Components;

LightComponent::LightComponent():
m_light(std::make_unique<Engine::DirectionalLight>())
{
    auto dir = dynamic_cast<Engine::DirectionalLight*>(m_light.get());
    dir->SetDirection(Vec3(0,-1,0));
    dir->SetIntensity(1.0);
}

LightComponent::LightComponent(const LightComponent & rhs)
{
    switch(rhs.GetType())
    {
        case Engine::Light::LightType::Directional:
        {
            auto from = dynamic_cast<DirectionalLight*>(rhs.m_light.get());
            m_light = std::make_unique<DirectionalLight>(*from);
            break;
        }
        default:
        {
            m_light = std::make_unique<DirectionalLight>();
        }
    }
}

LightComponent::~LightComponent()
{

}

void LightComponent::Init()
{

}

std::unique_ptr<Engine::EntityComponent> LightComponent::Duplicate() const 
{
    return std::make_unique<LightComponent>(*this);
}

void LightComponent::OnTransformChanged(const Engine::Transform &tr)
{
    assert (m_light != nullptr);

    // If this component represents direction light we need to update 
    // its direction vector each time transform rotates
    if(m_light->GetType() == Light::LightType::Directional)
    {
        Mat4 rot = Transform::RotMatrixFromTransform(tr);
        auto dlight = dynamic_cast<DirectionalLight*>(m_light.get());
        dlight->SetDirection(rot * Vec4(0.f,-1.f,0.f, 0.0f));
    }
    
}

void LightComponent::SetType(Engine::Light::LightType type)
{
    if(GetLight()->GetType() != type)
    {
        switch (type)
        {
            case Engine::Light::LightType::Directional:
                m_light = std::make_unique<Engine::DirectionalLight>();
                break;
            default:
                throw std::invalid_argument("Given light type is not yet supported !");
        }
    }
}

Engine::Light::LightType LightComponent::GetType() const 
{
    assert (m_light != nullptr);
    return m_light->GetType();
}

Engine::Light * LightComponent::GetLight()
{
    return m_light.get();
}
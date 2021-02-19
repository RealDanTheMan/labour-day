#include "movementcomponent.hpp"

using namespace Engine::Components;

MovementComponentSerialiser::MovementComponentSerialiser() : EntityComponentSerialiser("MovementComponentClass")
{

}

MovementComponentSerialiser::~MovementComponentSerialiser()
{
    
}

bool MovementComponentSerialiser::Deserialise(
    EntityComponent* pComponent, 
    const ContentEntityComponentInfo * pComponentInfo,
    const ResourceCache *pResourceCache) const
{
    assert (pComponent != nullptr);

    auto pCom = reinterpret_cast<MovementComponent*>(pComponent);
    assert (pCom != nullptr);

    for(auto &prop : pComponentInfo->m_properties)
    {
        if(prop->m_name == "Speed")
        {
            float speed = std::stoi(prop->m_value);
            pCom->SetSpeed(speed);

            continue;
        }

        if(prop->m_name == "Direction")
        {
            Vec3 dir = SerialisationUtils::Vec3FromString(prop->m_value);
            pCom->SetDirection(dir);

            continue;
        }
    }

    return true;
}

bool MovementComponentSerialiser::DeserialiseAdd(
    Entity* pEntity, 
    const ContentEntityComponentInfo * pComponentInfo,
    const ResourceCache *pResourceCache) const
{
    assert (pEntity != nullptr);
    assert (pComponentInfo != nullptr);

    auto pCom = pEntity->Components().Add<MovementComponent>();
    assert (pCom != nullptr);

    bool stat = Deserialise(pCom, pComponentInfo, pResourceCache);
    if(stat)
    {
        return true;
    }

    return false;
}

MovementComponent::~MovementComponent()
{

}

void MovementComponent::Init()
{
    SetLookAt(Vec3(0,0,1));
}

std::unique_ptr<Engine::EntityComponent> MovementComponent::Duplicate() const
{
    auto dup = std::make_unique<MovementComponent>(*this);
    return dup;
}

void MovementComponent::SetSpeed(const float speed)
{
    m_speed = speed;
}

void MovementComponent::SetDirection(const Vec3 &dir)
{
    m_direction = dir;
}

void MovementComponent::SetLookAt(const Vec3 &dir)
{
    m_lookAt = dir;
}

void MovementComponent::SetPendingMovement(bool state)
{
    m_pending = state;
}

float MovementComponent::GetSpeed() const
{
    return m_speed;
}

Vec3 MovementComponent::GetDirection() const
{
    return m_direction;
}

Vec3 MovementComponent::GetLookAt() const
{
    return m_lookAt;
}

bool MovementComponent::IsPendingMovement() const
{
    return m_pending;
}
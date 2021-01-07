#include "movementcomponent.hpp"

using namespace Engine::Components;

MovementComponentSerialiser::MovementComponentSerialiser() : EntityComponentSerialiser("MovementComponentClass")
{

}

MovementComponentSerialiser::~MovementComponentSerialiser()
{
    
}

bool MovementComponentSerialiser::Deserialise(EntityComponent* pComponent, const ContentEntityComponentInfo * pComponentInfo) const
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

        if(prop->m_name == "Stop")
        {
            bool stop = SerialisationUtils::BoolFromString(prop->m_value);
            pCom->ToggleStop(stop);

            continue;
        }
    }

    return true;
}

bool MovementComponentSerialiser::DeserialiseAdd(Entity* pEntity, const ContentEntityComponentInfo * pComponentInfo) const
{
    assert (pEntity != nullptr);
    assert (pComponentInfo != nullptr);

    auto pCom = pEntity->Components().Add<MovementComponent>();
    assert (pCom != nullptr);

    bool stat = Deserialise(pCom, pComponentInfo);
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

void MovementComponent::ToggleStop(bool state)
{
    m_stop = state;
}

float MovementComponent::GetSpeed() const
{
    return m_speed;
}

Vec3 MovementComponent::GetDirection() const
{
    return m_direction;
}

bool MovementComponent::GetStop() const
{
    return m_stop;
}
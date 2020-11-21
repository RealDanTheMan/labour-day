#include "wobblecomponent.hpp"

using namespace Engine::Components;

WobbleComponentSerialiser::WobbleComponentSerialiser() : EntityComponentSerialiser("WobbleComponentClass")
{
}

WobbleComponentSerialiser::~WobbleComponentSerialiser()
{
}

bool WobbleComponentSerialiser::Deserialise(EntityComponent* pComponent, const ContentEntityComponentInfo * pComponentInfo) const
{
    assert (pComponent != nullptr);

    auto pCmp = reinterpret_cast<WobbleComponent*>(pComponent);
    assert (pCmp != nullptr);


    return true;
}

bool WobbleComponentSerialiser::DeserialiseAdd(Entity* pEntity, const ContentEntityComponentInfo * pComponentInfo) const
{
    assert (pEntity != nullptr);
    assert (pComponentInfo != nullptr);
    auto pCmp = pEntity->Components().Add<WobbleComponent>();
    assert (pCmp != nullptr);

    bool stat = Deserialise(pCmp, pComponentInfo);
    if(stat)
    {
        return true;
    }

    return false;
}

WobbleComponent::WobbleComponent():
m_doRotate(true),
m_doScale(true),
m_rotationSpeed(1.0f),
m_scaleSpeed(1.0f)
{
}

WobbleComponent::WobbleComponent(const WobbleComponent &rhs)
{
    m_doRotate = rhs.m_doRotate;
    m_doScale = rhs.m_doScale;
    m_rotationSpeed = rhs.m_rotationSpeed;
    m_scaleSpeed = rhs.m_scaleSpeed;
}

WobbleComponent::~WobbleComponent()
{
}

void WobbleComponent::Init()
{
}

std::unique_ptr<Engine::EntityComponent> WobbleComponent::Duplicate() const
{
    auto dup = std::make_unique<WobbleComponent>();
    dup->m_doRotate = DoRotate();
    dup->m_doScale = DoScale();
    dup->m_rotationSpeed = RotationSpeed();
    dup->m_scaleSpeed = ScaleSpeed();

    return dup;
}

bool WobbleComponent::DoRotate() const
{
    return m_doRotate;
}

bool WobbleComponent::DoScale() const
{
    return m_doScale;
}

float WobbleComponent::RotationSpeed() const
{
    return m_rotationSpeed;
}

float WobbleComponent::ScaleSpeed() const
{
    return m_scaleSpeed;
}
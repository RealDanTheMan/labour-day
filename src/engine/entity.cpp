#include "entity.hpp"

using namespace Engine;

Entity::Entity():
    m_uuid(0),
    m_components(nullptr)
{
    m_components = std::make_unique<EntityComponentCollection>();
}

EntityComponentCollection& Entity::Components()
{
    assert (m_components != nullptr);
    return *m_components;
}

std::unique_ptr<Entity> Entity::Duplicate() const 
{
    auto dup = std::make_unique<Entity>();
    dup->m_components = m_components->Duplicate();

    return dup;
}
#include "entity.hpp"

using namespace Engine;

Entity::Entity():
    m_uuid(0),
    m_components(EntityComponentCollection())
{
}

Entity::Entity(const Entity &rhs):
    m_uuid(rhs.m_uuid),
    m_components(rhs.m_components)
{
}

EntityComponentCollection& Entity::Components()
{
    return m_components;
}


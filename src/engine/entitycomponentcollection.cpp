#include "entitycomponentcollection.hpp"

using namespace Engine;

EntityComponentCollection::EntityComponentCollection():
    m_count(0)
{
}

EntityComponentCollection::EntityComponentCollection(const EntityComponentCollection &rhs):
    m_count(rhs.m_count)
{
}

const uint32_t EntityComponentCollection::Count() const
{
    return m_components.size();
}
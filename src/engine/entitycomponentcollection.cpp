#include "entitycomponentcollection.hpp"

using namespace Engine;

EntityComponentCollection::EntityComponentCollection():
    m_count(0)
{
}

const uint32_t EntityComponentCollection::Count() const
{
    return m_components.size();
}

std::unique_ptr<EntityComponentCollection> EntityComponentCollection::Duplicate() const
{
    auto dup = std::make_unique<EntityComponentCollection>();
    for(uint32_t i=0; i < Count(); i++)
    {
        auto cdup = m_components[i]->Duplicate();
        dup->m_components.push_back(std::move(cdup));
    }

    return dup;
}
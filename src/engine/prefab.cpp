#include "prefab.hpp"
#include "debugging.hpp"

using namespace Engine;

Prefab::Prefab(const Entity &entity)
{
    m_entity = entity.Duplicate();
}

void Prefab::Unload()
{
    m_entity.reset(nullptr);
}

const Entity * const Prefab::PrefabEntity() const
{
    return m_entity.get();
}

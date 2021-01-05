#include "prefab.hpp"
#include "debugging.hpp"

using namespace Engine;

Prefab::Prefab(const Entity &entity)
{
    std::vector<std::unique_ptr<Entity>> dups = entity.DuplicateHierarchy();
    for(auto &dup : dups)
    {
        m_entities.push_back(std::move(dup));
    }
}

Prefab::Prefab(const std::vector<std::unique_ptr<Entity>> &entities)
{
    for(auto & entity : entities)
    {
        if(entity->IsRoot())
        {
            std::vector<std::unique_ptr<Entity>> dups = entity->DuplicateHierarchy();
            for(auto &dup : dups)
            {
                m_entities.push_back(std::move(dup));
            }
        }
    }
}

void Prefab::Unload()
{
    m_entities.clear();
}

std::vector<const Entity*> Prefab::GetRootEntities() const
{
    std::vector<const Entity*> entities;
    for(auto &entity : m_entities)
    {
        if(entity->IsRoot())
        {
            entities.push_back(entity.get());
        }
    }

    return entities;
}
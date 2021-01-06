#include "ecssys.hpp"

using namespace Engine;

ECSSys::ECSSys()
{

}

void ECSSys::Init(const uint32_t poolSize)
{
    for(uint32_t i=0; i < poolSize; i++)
    {
        m_pool.push_back(std::make_unique<Entity>());
    }
}

void ECSSys::Update(const double deltaTime)
{
    // Make sure all components are fully initialised
    std::vector<EntityComponent*> coms = GetAllComponentNotReady();
    for(auto &com : coms)
    {
        com->PreInit();
    }

    // Invoke all component precesses update ticks
    for(uint32_t i=0; i < m_procs.size(); i++)
    {
        std::vector<Entity*> entities = GetAllEntities();
        m_procs[i]->ProcessEntities(entities, deltaTime);
    }
}

void ECSSys::Terminate()
{
    m_liveEntities.clear();
    m_components.clear();
    m_pool.clear();
    m_procs.clear();
}

Entity* ECSSys::CreateEntity()
{
    assert (m_pool.size() > 0);
    std::unique_ptr<Entity> h = std::move(m_pool.back());
    m_pool.pop_back();

    m_liveEntities.push_back(std::move(h));
    return m_liveEntities.back().get();
}

Entity* ECSSys::CreateEntity(const Prefab * const pref)
{
    assert (pref != nullptr);
    assert (m_pool.size() > 0);

    std::vector<const Entity*> prefabEntities = pref->GetRootEntities();
    assert (prefabEntities.size() == 1);

    std::vector<std::unique_ptr<Entity>> dups = prefabEntities[0]->DuplicateHierarchy();
    Entity* root;
    for(auto &dup : dups)
    {
        if(dup == dups[0])
        {
            m_liveEntities.push_back(std::move(dup));
            root = m_liveEntities.back().get();
        }
        else 
        {
            m_liveEntities.push_back(std::move(dup));
        }
    }

    return root;
}

std::vector<Entity*> ECSSys::GetAllEntities()
{
    std::vector<Entity*> entities;
    for(auto &entity : m_liveEntities)
    {
        entities.push_back(entity.get());
    }

    return entities;
}

std::vector<EntityComponent*> ECSSys::GetAllComponentNotReady()
{
    std::vector<EntityComponent*> coms;
    for(auto &entity : m_liveEntities)
    {
        for(auto &com : entity->Components().Get())
        {
            if(!com->IsReady())
            {
                coms.push_back(com);
            }
        }
    }

    return coms;
}
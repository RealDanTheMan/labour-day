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

void ECSSys::Update()
{
    for(uint32_t i=0; i < m_procs.size(); i++)
    {
        std::vector<Entity*> entities;
        AllAssets(entities);
        m_procs[i]->ProcessEntities(entities);
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
    return nullptr;
}

void ECSSys::AllAssets(std::vector<Entity*>& outVec)
{
    for(uint32_t i=0; i < m_liveEntities.size(); i++)
    {
        outVec.push_back(m_liveEntities[i].get());
    }
}
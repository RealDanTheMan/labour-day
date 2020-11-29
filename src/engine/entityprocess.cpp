#include "entityprocess.hpp"

using namespace Engine;


EntityProcess::EntityProcess():
m_currentTime(0.1f),
m_currentTimeDelta(1.0f)
{

}

void EntityProcess::ProcessEntities(std::vector<Entity*>& entities)
{
    m_currentTime += m_currentTimeDelta;
    for(auto &entity : entities)
    {
        if(IsValidEntity(entity))
        {
            OnUpdate(entity);
        }
    }
}

void EntityProcess::OnUpdate(Entity* const entity)
{
}

bool EntityProcess::IsValidEntity (Entity * const entity)
{
    return true;
}

float EntityProcess::CurrentTime() const
{
    return m_currentTime;
}

float EntityProcess::CurrentTimeDelta() const
{
    return m_currentTimeDelta;
}
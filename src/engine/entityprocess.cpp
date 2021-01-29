#include "entityprocess.hpp"

using namespace Engine;


EntityProcess::EntityProcess():
m_currentTime(0.0f),
m_currentTimeDelta(0.0f)
{

}

void EntityProcess::Init(const IGraphicsUtils *graphics)
{
    m_graphics = graphics;
}

void EntityProcess::ProcessEntities(std::vector<Entity*>& entities, const double deltaTime)
{
    m_currentTimeDelta = deltaTime;
    m_currentTime += deltaTime;

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

const IGraphicsUtils * const EntityProcess::Graphics() const
{
    assert (m_graphics != nullptr);
    return m_graphics;
}
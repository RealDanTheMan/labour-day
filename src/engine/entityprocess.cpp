#include "entityprocess.hpp"

using namespace Engine;


EntityProcess::EntityProcess()
{

}

void EntityProcess::ProcessEntities(std::vector<Entity*>& entities)
{
    for(auto &entity : entities)
    {
        OnUpdate(entity);
    }
}

void EntityProcess::OnUpdate(Entity* const entity)
{

}
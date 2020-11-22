#include "entityprocess.hpp"

using namespace Engine;


EntityProcess::EntityProcess()
{

}

void EntityProcess::ProcessEntities(std::vector<Entity*>& entities)
{
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
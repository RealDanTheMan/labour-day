#ifndef ENTITY_PROCESS_HPP_
#define ENTITY_PROCESS_HPP_


#include "entity.hpp"

namespace Engine
{
    class EntityProcess
    {
        public:
        EntityProcess();

        void ProcessEntities(std::vector<Entity*>& entities);
        virtual void OnUpdate(Entity* const entity);
        
        private:
        virtual bool IsValidEntity(Entity * const Entity);
    };
}

#endif
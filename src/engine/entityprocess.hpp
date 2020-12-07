#ifndef ENTITY_PROCESS_HPP_
#define ENTITY_PROCESS_HPP_


#include "entity.hpp"

namespace Engine
{
    class EntityProcess
    {
        public:
        EntityProcess();

        void ProcessEntities(std::vector<Entity*>& entities, const double deltaTime);
        virtual void OnUpdate(Entity* const entity);

        float CurrentTime() const;
        float CurrentTimeDelta() const;
        
        private:
        virtual bool IsValidEntity(Entity * const Entity);
        float m_currentTime;
        float m_currentTimeDelta;
    };
}

#endif
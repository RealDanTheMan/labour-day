#ifndef ENTITY_HPP_
#define ENTITY_HPP_

#include "entitycomponentcollection.hpp"

namespace Engine
{
    class Entity
    {
        public:
            Entity();
            Entity(const Entity &rhs)=delete;

            EntityComponentCollection& Components();
            std::unique_ptr<Entity> Duplicate() const;
        private:
            uint32_t m_uuid;
            std::unique_ptr<EntityComponentCollection> m_components;
    };
}

#endif

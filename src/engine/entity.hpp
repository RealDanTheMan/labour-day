#ifndef ENTITY_HPP_
#define ENTITY_HPP_

#include "entitycomponentcollection.hpp"

namespace Engine
{
    class Entity
    {
        public:
            Entity();
            Entity(const Entity &rhs);

            EntityComponentCollection& Components();
        private:
            uint32_t m_uuid;
            EntityComponentCollection m_components;
    };
}

#endif

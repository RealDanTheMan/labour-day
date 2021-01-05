#ifndef ENTITY_HPP_
#define ENTITY_HPP_

#include "entitycomponentcollection.hpp"
#include "transform.hpp"

namespace Engine
{
    class Entity
    {
        public:
            Entity();
            Entity(const Entity &rhs)=delete;

            EntityComponentCollection& Components();
            std::unique_ptr<Entity> Duplicate() const;
            std::vector<std::unique_ptr<Entity>> DuplicateHierarchy() const;
            void SetParent(Entity *parent);
            Entity * GetParent();
            bool IsRoot() const;
        private:
            uint32_t m_uuid;
            std::unique_ptr<EntityComponentCollection> m_components;
            Entity* m_parent;
            std::vector<Entity*> m_children;

            ChangedDelegate OnParentTransformChangedDelegate;
            void OnParentTransformChanged(int);
    };
}

#endif

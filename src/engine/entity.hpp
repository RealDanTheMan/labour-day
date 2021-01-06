#ifndef ENTITY_HPP_
#define ENTITY_HPP_

#include "entitycomponentcollection.hpp"
#include "transform.hpp"

namespace Engine
{
    namespace Components
    {
        class TransformComponent;
    }

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

            Components::TransformComponent * GetTransform();
        private:
            uint32_t m_uuid;
            std::unique_ptr<EntityComponentCollection> m_components;
            std::vector<Entity*> m_children;
            Entity* m_parent;

            // Event delegates
            ComponentAddedDelegate OnComponentAddedDelegate;
            ChangedDelegate OnParentTransformChangedDelegate;
            ChangedDelegate OnLocalTransformChangedDelegate;

            // Event handlers
            void OnComponentAdded(EntityComponent *com);
            void OnParentTransformChanged(int);
            void OnLocalTransformChanged(int);
            void UpdateEntityTransforms();
    };
}

#endif

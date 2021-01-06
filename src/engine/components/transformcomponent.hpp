#ifndef TRANSFORM_COMPONENT_HPP_
#define TRANSFORM_COMPONENT_HPP_

#include "../entitycomponent.hpp"
#include "../entityserialiser.hpp"
#include "../transform.hpp"

namespace Engine
{
    namespace Components
    {
        class TransformComponentSerialiser : public EntityComponentSerialiser
        {
            public:
            TransformComponentSerialiser();
            virtual ~TransformComponentSerialiser();
            virtual bool Deserialise(EntityComponent* pComponent, const ContentEntityComponentInfo * pComponentInfo) const override;
            virtual bool DeserialiseAdd(Entity* pEntity, const ContentEntityComponentInfo * pComponentInfo) const override;
        };


        class TransformComponent : public EntityComponent
        {
            public:
            TransformComponent();
            TransformComponent(const TransformComponent &rhs);
            virtual ~TransformComponent() override;

            void Init() override;
            std::unique_ptr<EntityComponent> Duplicate() const override;

            Transform & GetTransform();
            Transform & GetTransformLocal();
            const Transform & GetTransform() const;
            const Transform & GetTransformLocal() const;
            
            void HandleTransformChanged(int);
            virtual void OnTransformChanged(const Transform &tr);

            void SetLocalTranslation(const Vec3 &translation);
            void SetLocalRotation(const Vec3 &rotation);
            void SetLocalScale(const Vec3 &scale);

            Vec3 GetLocalTranslation() const;
            Vec3 GetLocalRotation() const;
            Vec3 GetLocalScale() const;

            private:
            Transform m_tr;
            Transform m_local;
            ChangedDelegate OnTransformChangedDelegate;
        } ;
    }
}

#endif
#ifndef MOVEMENT_COMPONENT_HPP_
#define MOVEMENT_COMPONENT_HPP_

#include "../entitycomponent.hpp"
#include "../entityserialiser.hpp"

namespace Engine
{
    namespace Components
    {
        class MovementComponentSerialiser : public EntityComponentSerialiser
        {
            public:
            MovementComponentSerialiser();
            virtual ~MovementComponentSerialiser();

            virtual bool Deserialise(EntityComponent* pComponent, const ContentEntityComponentInfo * pComponentInfo) const override;
            virtual bool DeserialiseAdd(Entity* pEntity, const ContentEntityComponentInfo * pComponentInfo) const override;
        };

        class MovementComponent : public EntityComponent
        {
            public:
            MovementComponent() = default;
            MovementComponent(const MovementComponent &rhs) = default;
            virtual ~MovementComponent() override;

            virtual void Init() override;
            virtual std::unique_ptr<EntityComponent> Duplicate() const override;

            void SetSpeed(const float speed);
            void SetDirection(const Vec3 &dir);
            void SetPendingMovement(const bool state);

            float GetSpeed() const;
            Vec3 GetDirection() const;
            bool IsPendingMovement() const;

            private:
            float m_speed;
            Vec3 m_direction;
            bool m_pending;
        };
    }
}

#endif
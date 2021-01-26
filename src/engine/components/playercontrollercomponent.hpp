#ifndef PLAYER_CONTROLLER_COMPONENT_HPP_
#define PLAYER_CONTROLLER_COMPONENT_HPP_

#include "controllercomponent.hpp"
#include "movementcomponent.hpp"

namespace Engine
{
    namespace Components
    {
        class PlayerControllerComponentSerialiser : public EntityComponentSerialiser
        {
            public:
            PlayerControllerComponentSerialiser();
            virtual ~PlayerControllerComponentSerialiser();

            virtual bool Deserialise(
                EntityComponent* pComponent, 
                const ContentEntityComponentInfo * pComponentInfo,
                const ResourceCache *pResourceCache) const override;

            virtual bool DeserialiseAdd(
                Entity* pEntity, 
                const ContentEntityComponentInfo * pComponentInfo,
                const ResourceCache *pResourceCache) const override;
        };

        class PlayerControllerComponent : public ControllerComponent
        {
            public:
            PlayerControllerComponent() = default;
            PlayerControllerComponent(const PlayerControllerComponent &rhs) = default;
            virtual ~PlayerControllerComponent() override;
            
            virtual void Init() override;
            virtual std::unique_ptr<Engine::EntityComponent> Duplicate() const override;
            virtual void SetupInputActions() override;
            virtual void OnAction(const ControllerAction &action) override;

            void ToggleAutoPossess(const bool toggle);
            const bool AutoPossesses() const;
            MovementComponent * GetCapturedMovement();
            const Vec3 GetMovementDir() const;

            protected:
            bool m_autoPossess;

            private:
            float m_forward;
            float m_backward;
            float m_left;
            float m_right;
        };
    }
}

#endif
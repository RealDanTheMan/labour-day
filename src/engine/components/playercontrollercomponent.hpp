#ifndef PLAYER_CONTROLLER_COMPONENT_HPP_
#define PLAYER_CONTROLLER_COMPONENT_HPP_

#include "controllercomponent.hpp"

namespace Engine
{
    namespace Components
    {
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

            private:
            void OnForwardAction();
            void OnBackwardAction();
            void OnLeftAction();
            void OnRightAction();
        };
    }
}

#endif
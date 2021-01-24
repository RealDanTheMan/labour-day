#ifndef CONTROLLER_COMPONENT_HPP_
#define CONTROLLER_COMPONENT_HPP_

#include "transformcomponent.hpp"

#include "../keymap.hpp"
#include <functional>

namespace Engine
{
    namespace Components
    {
        struct ControllerAction
        {
            enum KeyState
            {
                Up = 0,
                Down = 1
            };

            ControllerAction(const std::string &name, const uint32_t key, KeyState state);
            ControllerAction(const ControllerAction &rhs);
            std::string m_name;
            uint32_t m_key;
            KeyState m_state;
        };

        class ControllerComponent : public EntityComponent
        {
            public:
            ControllerComponent() = default;
            ControllerComponent(const ControllerComponent &rhs);
            virtual ~ControllerComponent() override;

            virtual void Init() override;
            virtual std::unique_ptr<Engine::EntityComponent> Duplicate() const =0;
            virtual void SetupInputActions()=0;
            virtual void OnAction(const ControllerAction &action)=0;

            std::vector<std::unique_ptr<ControllerAction>> & InputActions();
            void CaptureComponent(EntityComponent * target);
            EntityComponent * CapturedComponent();

            private:
            std::vector<std::unique_ptr<ControllerAction>> m_actions;
            EntityComponent * m_captured;
        };
    }
}

#endif
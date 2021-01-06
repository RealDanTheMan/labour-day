#ifndef CONTROLLER_COMPONENT_HPP_
#define CONTROLLER_COMPONENT_HPP_

#include "transformcomponent.hpp"

namespace Engine
{
    namespace Components
    {
        struct ControllerAction
        {
            std::string m_name;
        };

        class ControllerComponent : public TransformComponent
        {
            public:
            ControllerComponent() = default;
            ControllerComponent(const ControllerComponent &rhs) = default;
            virtual ~ControllerComponent() override;

            virtual void Init() override;
            virtual std::unique_ptr<EntityComponent> Duplicate() const override;
            virtual void SetupInputActions()=0;

            std::vector<std::unique_ptr<ControllerAction>> & InputActions();

            private:
            std::vector<std::unique_ptr<ControllerAction>> m_actions;
        };
    }
}

#endif
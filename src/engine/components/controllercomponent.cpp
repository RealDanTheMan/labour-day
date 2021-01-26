#include "controllercomponent.hpp"

using namespace Engine::Components;

ControllerAction::ControllerAction(const std::string &name, const uint32_t key):
    m_name(name),
    m_key(key),
    m_state(InputManager::KeyState::Inactive)
{

}

ControllerAction::ControllerAction(const ControllerAction &rhs):
    m_name(rhs.m_name),
    m_key(rhs.m_key),
    m_state(rhs.m_state)
{

}

ControllerComponent::ControllerComponent(const ControllerComponent &rhs):
m_captured(rhs.m_captured)
{
    for(auto &action : rhs.m_actions)
    {
        auto dupAction = std::make_unique<ControllerAction>(*action);
        m_actions.push_back(std::move(dupAction));
    }
}

ControllerComponent::~ControllerComponent()
{

}

void ControllerComponent::Init()
{
    SetupInputActions();
}

std::vector<std::unique_ptr<ControllerAction>> & ControllerComponent::InputActions()
{
    return m_actions;
}

void ControllerComponent::CaptureComponent(EntityComponent * target)
{
    m_captured = target;
}

Engine::EntityComponent * ControllerComponent::CapturedComponent()
{
    return m_captured;
}
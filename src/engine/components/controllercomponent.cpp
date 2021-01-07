#include "controllercomponent.hpp"

using namespace Engine::Components;

ControllerAction::ControllerAction(const std::string &name, const uint32_t key, KeyState state):
    m_name(name),
    m_key(key),
    m_state(state)
{

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
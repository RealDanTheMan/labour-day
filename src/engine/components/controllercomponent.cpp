#include "controllercomponent.hpp"

using namespace Engine::Components;

ControllerComponent::~ControllerComponent()
{

}

void ControllerComponent::Init()
{
    SetupInputActions();
}

std::unique_ptr<Engine::EntityComponent> ControllerComponent::Duplicate() const
{
    return nullptr;
}

std::vector<std::unique_ptr<ControllerAction>> & ControllerComponent::InputActions()
{
    return m_actions;
}
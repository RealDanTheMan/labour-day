#include "playercontrollercomponent.hpp"

using namespace Engine::Components;

PlayerControllerComponent::~PlayerControllerComponent()
{

}

void PlayerControllerComponent::Init()
{
    ControllerComponent::Init();
}

std::unique_ptr<Engine::EntityComponent> PlayerControllerComponent::Duplicate() const
{
    return nullptr;
}

void PlayerControllerComponent::SetupInputActions() 
{
}
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
    // Simple walk input mapping example
    auto forward = std::make_unique<ControllerAction>("Forward", KEY_W, ControllerAction::KeyState::Down);
    auto backward = std::make_unique<ControllerAction>("Backward", KEY_S, ControllerAction::KeyState::Down);
    auto left = std::make_unique<ControllerAction>("Left", KEY_A, ControllerAction::KeyState::Down);
    auto right = std::make_unique<ControllerAction>("Right", KEY_D, ControllerAction::KeyState::Down);
    
    InputActions().push_back(std::move(forward));
    InputActions().push_back(std::move(backward));
    InputActions().push_back(std::move(left));
    InputActions().push_back(std::move(right));
}

void PlayerControllerComponent::OnAction(const ControllerAction &action)
{
    if(GetCapturedMovement() == nullptr)
    {
        // If we arent posessing anything in the scene 
        // there is no need for us to do anything
        return;
    }

    const float scale = 0.1f;
    Vec3 dir = Vec3(0,0,0);

    // TMP for testing
    // TODO: Implement and use character movement component instead of doing logic here
    if(action.m_state == ControllerAction::KeyState::Down)
    {
        if(action.m_name == "Forward")
        {
            dir.z = 1.0f;
            //tr->GetTransform().Translate(Vec3(0,0,scale));
        }

        if(action.m_name == "Backward")
        {
            dir.z = -1.0f;
            //tr->GetTransform().Translate(Vec3(0,0,-scale));
        }

        if(action.m_name == "Left")
        {
            dir.x = 1.0f;
            //tr->GetTransform().Translate(Vec3(scale,0,0));
        }

        if(action.m_name == "Right")
        {
            dir.x = -1.0f;
            //tr->GetTransform().Translate(Vec3(-scale,0,0));
        }
    }

    if(dir == Vec3(0,0,0))
    {
        GetCapturedMovement()->SetPendingMovement(false);
    }
    else
    {
        GetCapturedMovement()->SetDirection(glm::normalize(dir));
        GetCapturedMovement()->SetPendingMovement(true);
    }
}

MovementComponent * PlayerControllerComponent::GetCapturedMovement()
{
    return dynamic_cast<MovementComponent*>(CapturedComponent());
}
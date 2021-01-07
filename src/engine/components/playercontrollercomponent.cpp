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

    auto forwardStop = std::make_unique<ControllerAction>("Forward", KEY_W, ControllerAction::KeyState::Up);
    auto backwardStop = std::make_unique<ControllerAction>("Backward", KEY_S, ControllerAction::KeyState::Up);
    auto leftStop = std::make_unique<ControllerAction>("Left", KEY_A, ControllerAction::KeyState::Up);
    auto rightStop = std::make_unique<ControllerAction>("Right", KEY_D, ControllerAction::KeyState::Up);
    
    InputActions().push_back(std::move(forward));
    InputActions().push_back(std::move(backward));
    InputActions().push_back(std::move(left));
    InputActions().push_back(std::move(right));

    InputActions().push_back(std::move(forwardStop));
    InputActions().push_back(std::move(backwardStop));
    InputActions().push_back(std::move(leftStop));
    InputActions().push_back(std::move(rightStop));
}

void PlayerControllerComponent::OnAction(const ControllerAction &action)
{
    if(CapturedComponent() == nullptr)
    {
        // If we arent posessing anything in the scene 
        // there is no need for us to do anything
        return;
    }

    TransformComponent *tr = dynamic_cast<TransformComponent*>(CapturedComponent());
    assert (tr != nullptr);

    const float scale = 0.1f;

    // TMP for testing
    // TODO: Implement and use character movement component instead of doing logic here
    if(action.m_state == ControllerAction::KeyState::Down)
    {
        if(action.m_name == "Forward")
        {
            tr->GetTransform().Translate(Vec3(0,0,scale));
        }

        if(action.m_name == "Backward")
        {
            tr->GetTransform().Translate(Vec3(0,0,-scale));
        }

        if(action.m_name == "Left")
        {
            tr->GetTransform().Translate(Vec3(scale,0,0));
        }

        if(action.m_name == "Right")
        {
            tr->GetTransform().Translate(Vec3(-scale,0,0));
        }
    }
}
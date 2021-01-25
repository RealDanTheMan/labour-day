#include "playercontrollercomponent.hpp"

using namespace Engine::Components;

PlayerControllerComponentSerialiser::PlayerControllerComponentSerialiser() : EntityComponentSerialiser("PlayerControllerComponentClass")
{

}

PlayerControllerComponentSerialiser::~PlayerControllerComponentSerialiser()
{
    
}

bool PlayerControllerComponentSerialiser::Deserialise(
    EntityComponent* pComponent, 
    const ContentEntityComponentInfo * pComponentInfo,
    const ResourceCache *pResourceCache) const
{
    assert (pComponent != nullptr);

    auto pCom = reinterpret_cast<PlayerControllerComponent*>(pComponent);
    assert (pCom != nullptr);

    for(auto &pProperty : pComponentInfo->m_properties)
    {
        if(pProperty->m_name == "AutoPossess")
        {
            bool autoPossess = SerialisationUtils::BoolFromString(pProperty->m_value);
            pCom->ToggleAutoPossess(autoPossess);

            continue;
        }
    }

    return true;
}

bool PlayerControllerComponentSerialiser::DeserialiseAdd(
    Entity* pEntity, 
    const ContentEntityComponentInfo * pComponentInfo,
    const ResourceCache *pResourceCache) const
{
    assert (pEntity != nullptr);
    assert (pComponentInfo != nullptr);

    auto pCom = pEntity->Components().Add<PlayerControllerComponent>();
    assert (pCom != nullptr);

    bool stat = Deserialise(pCom, pComponentInfo, pResourceCache);
    if(stat)
    {
        return true;
    }

    return false;
}

PlayerControllerComponent::~PlayerControllerComponent()
{

}

void PlayerControllerComponent::Init()
{
    ControllerComponent::Init();
}

std::unique_ptr<Engine::EntityComponent> PlayerControllerComponent::Duplicate() const
{
    return std::make_unique<PlayerControllerComponent>(*this);
}

void PlayerControllerComponent::SetupInputActions() 
{
    // Simple walk input mapping example
    auto forward = std::make_unique<ControllerAction>("Forward", KEY_W, InputManager::KeyState::Active);
    auto backward = std::make_unique<ControllerAction>("Backward", KEY_S, InputManager::KeyState::Active);
    auto left = std::make_unique<ControllerAction>("Left", KEY_A, InputManager::KeyState::Active);
    auto right = std::make_unique<ControllerAction>("Right", KEY_D, InputManager::KeyState::Active);
    
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
    if(action.m_state == InputManager::KeyState::Active)
    {
        if(action.m_name == "Forward")
        {
            dir.z = 1.0f;
        }

        if(action.m_name == "Backward")
        {
            dir.z = -1.0f;
        }

        if(action.m_name == "Left")
        {
            dir.x = 1.0f;
        }

        if(action.m_name == "Right")
        {
            dir.x = -1.0f;
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

void PlayerControllerComponent::ToggleAutoPossess(const bool toggle)
{
    m_autoPossess = toggle;
}

const bool PlayerControllerComponent::AutoPossesses() const
{
    return m_autoPossess;
}
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
    
    m_forward = 0.0f;
    m_backward = 0.0f;
    m_left = 0.0f;
    m_right = 0.0f;
}

std::unique_ptr<Engine::EntityComponent> PlayerControllerComponent::Duplicate() const
{
    return std::make_unique<PlayerControllerComponent>(*this);
}

void PlayerControllerComponent::SetupInputActions() 
{
    // Simple walk input mapping example
    auto forward = std::make_unique<ControllerAction>("Forward", KEY_W);
    auto backward = std::make_unique<ControllerAction>("Backward", KEY_S);
    auto left = std::make_unique<ControllerAction>("Left", KEY_A);
    auto right = std::make_unique<ControllerAction>("Right", KEY_D);
    
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

    if(action.m_name == "Forward")
    {
        switch (action.m_state)
        {
            case InputManager::Active:
                //D_MSG("Forward State: Active !");
                m_forward = 1.0f;
                break;
            case InputManager::Released:
                //D_MSG("Forward State: Released !");
                m_forward = 0.0f;
                break;
        }
    }

    if(action.m_name == "Backward")
    {
        switch (action.m_state)
        {
            case InputManager::Active:
                //D_MSG("Backward State: Active !");
                m_backward = 1.0f;
                break;
            case InputManager::Released:
                //D_MSG("Backward State: Released !");
                m_backward = 0.0f;
                break;
        }
    }

    if(action.m_name == "Left")
    {
        switch (action.m_state)
        {
            case InputManager::Active:
                //D_MSG("Left State: Active !");
                m_left = 1.0f;
                break;
            case InputManager::Released:
                //D_MSG("Left State: Released !");
                m_left = 0.0f;
                break;
        }
    }

    if(action.m_name == "Right")
    {
        switch (action.m_state)
        {
            case InputManager::Active:
                //D_MSG("Right State: Active !");
                m_right = 1.0f;
                break;
            case InputManager::Released:
                //D_MSG("Right State: Released !");
                m_right = 0.0f;
                break;
        }
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

const Vec3 PlayerControllerComponent::GetMovementDir() const
{
    const Vec3 tmp = Vec3(m_left - m_right, 0.0f, m_forward - m_backward);
    return tmp;
}
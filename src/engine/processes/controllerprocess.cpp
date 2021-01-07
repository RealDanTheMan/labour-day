#include "controllerprocess.hpp"
#include "../components/controllercomponent.hpp"
#include "../inputmanager.hpp"

using namespace Engine::Processes;

void ControllerProcess::OnUpdate(Entity * const entity)
{
    auto ctrl = entity->Components().GetFirst<Components::ControllerComponent>();
    for(auto &action : ctrl->InputActions())
    {
        if(Engine::InputManager::Instance().CheckKey(action->m_key) && 
                action->m_state == Components::ControllerAction::KeyState::Down)
        {
            ctrl->OnAction(*action);
            continue;
        }

        if(!Engine::InputManager::Instance().CheckKey(action->m_key) && 
                action->m_state == Components::ControllerAction::KeyState::Up)
        {
            ctrl->OnAction(*action);
            continue;
        }
    }
}

bool ControllerProcess::IsValidEntity(Entity * const entity)
{
    if(entity->Components().GetFirst<Components::ControllerComponent>() != nullptr)
    {
        return true;
    }

    return false;
}
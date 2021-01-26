#include "controllerprocess.hpp"
#include "../components/controllercomponent.hpp"
#include "../inputmanager.hpp"

using namespace Engine::Processes;

void ControllerProcess::OnUpdate(Entity * const entity)
{
    auto ctrl = entity->Components().GetFirst<Components::ControllerComponent>();
    for(auto &action : ctrl->InputActions())
    {
        Engine::InputManager::KeyState state = Engine::InputManager::Instance().CheckKey(action->m_key);
        if(state == InputManager::Active || state == InputManager::Released)
        {
            //D_MSG("ControllerComponent -> Action triggered !");
            
            Engine::Components::ControllerAction act(*action);
            act.m_state = state;
            ctrl->OnAction(act);
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
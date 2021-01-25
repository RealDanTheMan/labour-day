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
        if(action->m_state == state)
        {
            ctrl->OnAction(*action);
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
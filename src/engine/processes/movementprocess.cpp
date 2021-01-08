#include "movementprocess.hpp"
#include "../components/movementcomponent.hpp"
#include "../components/transformcomponent.hpp"

using namespace Engine::Processes;

void MovementProcess::OnUpdate(Engine::Entity * const entity)
{
    auto mov = entity->Components().GetFirst<Components::MovementComponent>();
    auto tr = entity->Components().GetFirst<Components::TransformComponent>();

    assert (mov != nullptr);
    assert (entity->IsRoot());

    if(mov->IsPendingMovement() && tr != nullptr)
    {
        Vec3 val = mov->GetDirection() * mov->GetSpeed() * CurrentTimeDelta();
        tr->GetTransform().Translate(val);
        mov->SetPendingMovement(false);
    }
}

bool MovementProcess::IsValidEntity(Engine::Entity * const entity)
{
    if(entity->Components().GetFirst<Components::MovementComponent>() != nullptr)
    {
        return true;
    }

    return false;
}
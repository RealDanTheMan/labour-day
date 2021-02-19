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

    // move transform towars target direction
    if(mov->IsPendingMovement() && tr != nullptr)
    {
        Vec3 lookat2D = glm::normalize(Vec3(mov->GetLookAt().x, 0.0f, mov->GetLookAt().z));
        Vec3 dir = glm::normalize(Vec3(mov->GetDirection().x, 0.0f, mov->GetDirection().z));
        Vec3 aim = glm::normalize(lookat2D + dir);
        float angle = glm::dot(dir, lookat2D);

        Vec3 val = dir * mov->GetSpeed() * CurrentTimeDelta();

        tr->GetTransform().Translate(val);
        mov->SetPendingMovement(false);

        const Vec3 from = Vec3(tr->GetTransform().Translation());
        const Vec3 to = Vec3(from + (Vec3(10,10,10) * dir));
        Graphics()->DrawLineGizmo(from, to);
    }

    // Rotate to face lookat direction vector
    // For now we only rotate along Z
    //Vec3 face = Vec3(0,0,1);
    //float angle = glm::dot(mov->GetLookAt(), face);
    //float deg = glm::degrees(angle);
    //tr->GetTransform().SetRotation(Vec3(0,deg,0));
}

bool MovementProcess::IsValidEntity(Engine::Entity * const entity)
{
    if(entity->Components().GetFirst<Components::MovementComponent>() != nullptr)
    {
        return true;
    }

    return false;
}
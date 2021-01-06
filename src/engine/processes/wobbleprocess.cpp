#include "wobbleprocess.hpp"
#include "../components/wobblecomponent.hpp"
#include "../components/transformcomponent.hpp"

using namespace Engine::Processes;

void WobbleProcess::OnUpdate(Entity * const entity)
{
    auto cWobble = entity->Components().GetFirst<Engine::Components::WobbleComponent>();
    auto cTr = entity->Components().GetFirst<Engine::Components::TransformComponent>();
    
    assert (cWobble != nullptr);
    assert (cTr != nullptr);
    
    if(cTr != nullptr)
    {
        if(cWobble->DoRotate())
        {
            const Vec3 rot = Vec3(1.0f, 1.0f, 1.0f) * cWobble->RotationSpeed() * CurrentTimeDelta();
            cTr->GetTransform().Rotate(rot);
        }

        if(cWobble->DoScale())
        {
            const float min = 0.5f;
            const float max = 2.0f;
            float num;
            float t = modff(CurrentTime() / cWobble->ScaleSpeed(), &num);

            assert (min > 0.0);
            assert (max > 0.0 && max > min);
            assert (t >= 0.0f && t <=1.0f);

            t *= 2.0f;
            if(t > 1.0f)
            {
                t = 2.0f - t;
            }

            const float scale = ((1.0 - t) * min) + (t * max);
            cTr->GetTransform().SetScale(scale);
        }
    }
}

bool WobbleProcess::IsValidEntity (Entity * const entity)
{
    if (entity->Components().GetFirst<Components::WobbleComponent>() != nullptr && 
        entity->Components().GetFirst<Components::TransformComponent>() != nullptr)
    {
        return true;
    }
    
    return false;
}
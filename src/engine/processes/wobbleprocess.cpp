#include "wobbleprocess.hpp"
#include "../components/wobblecomponent.hpp"
#include "../components/modelcomponent.hpp"

using namespace Engine::Processes;

void WobbleProcess::OnUpdate(Entity * const entity)
{
    auto cWobble = entity->Components().Get<Engine::Components::WobbleComponent>();
    auto cModel = entity->Components().Get<Engine::Components::ModelComponent>();
    
    assert (cWobble != nullptr);
    if(cModel != nullptr)
    {
        assert (cModel->ModelHandle() != nullptr);

        if(cWobble->DoRotate())
        {
            const Vec3 rot = Vec3(1.0f, 1.0f, 1.0f) * cWobble->RotationSpeed() * CurrentTimeDelta();
            cModel->ModelHandle()->GetTransform().Rotate(rot);
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
            cModel->ModelHandle()->GetTransform().SetScale(scale);
            D_MSG(t);
        }
    }
}

bool WobbleProcess::IsValidEntity (Entity * const entity)
{
    if (entity->Components().Get<Components::WobbleComponent>() != nullptr && 
        entity->Components().Get<Components::ModelComponent>() != nullptr)
    {
        return true;
    }
    
    return false;
}
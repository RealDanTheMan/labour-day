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
            const Vec3 rot = Vec3(1.0f, 1.0f, 1.0f) * cWobble->RotationSpeed();
            cModel->ModelHandle()->GetTransform().Rotate(rot);
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
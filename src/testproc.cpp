#include "testproc.hpp"
#include "engine/components/modelcomponent.hpp"

TestProc::TestProc():
m_speed(1.0f)
{
    
}

void TestProc::OnUpdate(Engine::Entity * const entity)
{
    auto cmodel = entity->Components().Get<Engine::Components::ModelComponent>();
    assert (cmodel != nullptr);

    cmodel->ModelHandle()->GetTransform().Scale(0.01);
}
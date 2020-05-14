#include "testscene.hpp"
#include "testentity.hpp"
#include "testproc.hpp"
#include "engine/meshgen.hpp"
#include "engine/components/modelcomponent.hpp"


void TestScene::Initialize(Engine::EngineCore *core)
{
    m_core = core;

    assert (m_core != nullptr);
    assert (m_core->Shaders() != nullptr);
    assert (m_core->Shaders()->Ready());

    //std::unique_ptr<Engine::Mesh> msh = Engine::MeshGen::Cube(1.0f);
    std::unique_ptr<Engine::Mesh> msh = Engine::MeshGen::Box(1.0f, 1.0f, 1.0f);
    m_mesh = std::make_unique<Engine::Renderable>();
    //m_mesh->Init(msh->Vertices(), msh->Indices(), msh->VertexCount(), msh->IndexCount());
    m_mesh->Init(*msh);
    m_mesh->BindShader(m_core->Shaders()->Diff());
    assert (m_mesh->Ready());

    m_triangleModel = std::make_unique<Engine::Model>(*m_mesh);
    m_asset = m_core->ECS()->CreateEntity();
    assert (m_asset != nullptr);
    auto cmodel = m_asset->Components().Add<Engine::Components::ModelComponent>();
    cmodel->SetModel(m_triangleModel.get());
    assert (cmodel->ModelHandle() != nullptr);
    
    m_core->ECS()->CreateProcess<TestProc>();
    m_camera = std::make_unique<Engine::Camera>(1280, 720, 30, 1.7777);
    m_camera->GetTransform().Translate(Vec3(0, 0, -10));
}

Engine::Renderable* TestScene::TestTriangle()
{
    return m_mesh.get();
}

Engine::Entity* TestScene::Asset()
{
    return m_asset;
}

Engine::Camera* TestScene::Cam()
{
    return m_camera.get();
}

void TestScene::Update()
{
    assert (TestTriangle() != nullptr);
    assert (Cam() != nullptr);
}

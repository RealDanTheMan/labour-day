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

    std::unique_ptr<Engine::Mesh> msh = Engine::MeshGen::Triangle(1.0f);
    m_triangle = std::make_unique<Engine::Renderable>();
    m_triangle->Init(msh->Vertices(), msh->Indices(), msh->VertexCount(), msh->IndexCount());
    m_triangle->BindShader(m_core->Shaders()->FlatWhite());
    assert (m_triangle->Ready());

    m_triangleModel = std::make_unique<Engine::Model>(*m_triangle);
    m_asset = m_core->ECS()->CreateEntity();
    assert (m_asset != nullptr);
    auto cmodel = m_asset->Components().Add<Engine::Components::ModelComponent>();
    cmodel->SetModel(m_triangleModel.get());
    assert (cmodel->ModelHandle() != nullptr);
    
    m_core->ECS()->CreateProcess<TestProc>();
    m_camera = std::make_unique<Engine::Camera>();
}

Engine::Renderable* TestScene::TestTriangle()
{
    return m_triangle.get();
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

    Cam()->GetTransform().Translate(Vec3(0.001, 0.0, 0.0));
}

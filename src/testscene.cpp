#include "testscene.hpp"
#include "testentity.hpp"
#include "testproc.hpp"
#include "engine/meshgen.hpp"
#include "engine/components/modelcomponent.hpp"
#include "engine/material.hpp"
#include "engine/types.hpp"


void TestScene::Initialize(Engine::EngineCore *core)
{
    m_core = core;

    assert (m_core != nullptr);
    assert (m_core->Shaders() != nullptr);
    assert (m_core->Shaders()->Ready());

    m_tex = Engine::Texture2D::Load("/home/dantheman/local/dev/games/labour-day/labour-day/content/textures/test-01.jpg");
    assert (m_tex != nullptr);
    assert (m_tex->Ready());
    m_tex->GLPush();
    assert (m_tex->GLReady());
    //Engine::Texture2D::Write(m_tex.get(), "/home/dantheman/local/dev/games/labour-day/labour-day/content/textures/test-01-out.jpg");

    assert (m_core->Shaders()->Ready());
    m_mat = std::make_unique<Engine::Material>(*m_core->Shaders()->Diff1());
    m_mat->ShaderParameters()->SetTexValue("diff1map", m_tex.get());
    //m_mat->ShaderParameters()->SetValue("tint", Vec3(1, 0, 0));


    std::unique_ptr<Engine::Mesh> msh = Engine::MeshGen::Box(1.0f, 1.0f, 1.0f);
    m_mesh = std::make_unique<Engine::Renderable>();
    m_mesh->Init(*msh);
    m_mesh->BindShader(m_core->Shaders()->Diff1());
    assert (m_mesh->Ready());

    m_model = std::make_unique<Engine::Model>(*m_mesh, m_mat.get());
    m_asset = m_core->ECS()->CreateEntity();
    assert (m_asset != nullptr);
    auto cmodel = m_asset->Components().Add<Engine::Components::ModelComponent>();
    cmodel->SetModel(m_model.get());
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

    auto r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
    auto g = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
    auto b = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);

    //m_model->GetMaterial()->ShaderParameters()->SetValue("tint", Vec3(r, g, b));
}

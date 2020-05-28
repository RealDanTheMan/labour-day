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

    // Load asset resources
    m_cache = std::make_unique<Engine::AssetCache>();
    m_cache->AddTexture("/home/dantheman/local/dev/games/labour-day/labour-day/content/textures/test-01.jpg", "test-01");
    m_cache->AddMesh("/home/dantheman/local/dev/games/labour-day/labour-day/content/models/torus.obj", "torus");
    m_cache->AddPrefab("/home/dantheman/local/dev/games/labour-day/labour-day/content/prefabs/test.json", "test-prefab");

    D_MSG("Asset cache size");
    D_MSG(m_cache->Count());

    Engine::Texture2D* ptex = m_cache->GetTexture("test-01");
    Engine::Mesh* pmsh = m_cache->GetMesh("torus");
    Engine::Prefab* prf = m_cache->GetPrefab("test-prefab");

    assert (ptex != nullptr);
    assert (pmsh != nullptr);
    assert (prf != nullptr);


    // Load texture to GPU
    assert (ptex->Ready());
    ptex->GLPush();
    assert (ptex->GLReady());

    // Setup material properties
    assert (m_core->Shaders()->Ready());
    m_mat = std::make_unique<Engine::Material>(*m_core->Shaders()->Diff1());
    m_mat->ShaderParameters()->SetTexValue("diff1map", ptex);

    // Load mesh to GPU
    m_mesh = std::make_unique<Engine::Renderable>();
    m_mesh->Init(*pmsh);
    m_mesh->BindShader(m_core->Shaders()->Diff1());
    assert (m_mesh->Ready());

    // ECS setup
    m_model = std::make_unique<Engine::Model>(*m_mesh, m_mat.get());
    m_asset = m_core->ECS()->CreateEntity();
    assert (m_asset != nullptr);
    auto cmodel = m_asset->Components().Add<Engine::Components::ModelComponent>();
    cmodel->SetModel(m_model.get());
    assert (cmodel->ModelHandle() != nullptr);
    m_core->ECS()->CreateProcess<TestProc>();

    // Setup main scene camera
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

void TestScene::Free()
{
    m_cache->Free();
}

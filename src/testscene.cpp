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
    m_cache->AddMaterial("/home/dantheman/local/dev/games/labour-day/labour-day/content/materials/debugmat.json", "debugmat");
    m_cache->AddModel("/home/dantheman/local/dev/games/labour-day/labour-day/content/models/testmodel.json", "testmodel");
    m_cache->AddPrefab("/home/dantheman/local/dev/games/labour-day/labour-day/content/prefabs/test.json", "test-prefab");

    D_MSG("Asset cache size");
    D_MSG(m_cache->Count());

    Engine::Texture2D* ptex = m_cache->GetTexture("test-01");
    Engine::Mesh* pmsh = m_cache->GetMesh("torus");
    Engine::Model* pModel = m_cache->GetModel("testmodel");
    Engine::Prefab* prf = m_cache->GetPrefab("test-prefab");

    assert (ptex != nullptr);
    assert (pmsh != nullptr);
    assert (pModel != nullptr);
    assert (prf != nullptr);


    // Load texture to GPU
    assert (ptex->Ready());
    ptex->GLPush();
    assert (ptex->GLReady());

    // Setup material properties
    pModel->GetMaterial()->ShaderParameters()->SetTexValue("diff1map", ptex);

    // ECS setup
    m_core->ECS()->CreateEntity(prf);
    m_core->ECS()->CreateProcess<TestProc>();

    // Setup main scene camera
    m_camera = std::make_unique<Engine::Camera>(1280, 720, 30, 1.7777);
    m_camera->GetTransform().Translate(Vec3(0, 0, -10));
}

Engine::Camera* TestScene::Cam()
{
    return m_camera.get();
}

void TestScene::Free()
{
    m_cache->Free();
}

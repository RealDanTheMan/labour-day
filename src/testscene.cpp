#include "testscene.hpp"
#include "testentity.hpp"
#include "testproc.hpp"
#include "engine/meshgen.hpp"
#include "engine/components/modelcomponent.hpp"
#include "engine/components/cameracomponent.hpp"
#include "engine/processes/wobbleprocess.hpp"
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
    m_cache->AddFromManifest("/home/dantheman/local/dev/games/labour-day/labour-day/content/assetmanifest.json");

    D_MSG("Asset cache size");
    D_MSG(m_cache->Count());

    Engine::Texture2D* ptex = m_cache->GetTexture("TestTexture01");
    Engine::Model* pModel = m_cache->GetModel("MonkeModel");
    Engine::Prefab* prf1 = m_cache->GetPrefab("TorusTest");
    Engine::Prefab* prf2 = m_cache->GetPrefab("MonkeTest");
    Engine::Prefab* prf3 = m_cache->GetPrefab("TerrainTest");


    assert (ptex != nullptr);
    assert (pModel != nullptr);
    assert (prf1 != nullptr);
    assert (prf2 != nullptr);
    assert (prf3 != nullptr);


    // Load texture to GPU
    assert (ptex->Ready());
    ptex->GLPush();
    assert (ptex->GLReady());

    // Setup material properties
    //pModel->GetMaterial()->ShaderParameters()->SetTexValue("diff1map", ptex);

    // ECS setup
    m_core->ECS()->CreateEntity(prf1);
    auto player = m_core->ECS()->CreateEntity(prf2);
    m_core->ECS()->CreateEntity(prf3);
    m_core->ECS()->CreateProcess<TestProc>();
    m_core->ECS()->CreateProcess<Engine::Processes::WobbleProcess>();

    // Setup main scene camera - Default fallback if there are not camera components in the scene
    m_camera = std::make_unique<Engine::Camera>(30, 1.7777);
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

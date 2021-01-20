#include "testscene.hpp"
#include "testentity.hpp"
#include "testproc.hpp"
#include "engine/meshgen.hpp"
#include "engine/components/modelcomponent.hpp"
#include "engine/components/cameracomponent.hpp"
#include "engine/components/transformcomponent.hpp"
#include "engine/components/playercontrollercomponent.hpp"
#include "engine/components/terraincomponent.hpp"
#include "engine/processes/wobbleprocess.hpp"
#include "engine/processes/controllerprocess.hpp"
#include "engine/processes/movementprocess.hpp"
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

    Engine::Texture2D* ptex = m_cache->GetTexture("TerrainTest01");
    Engine::Prefab* prf1 = m_cache->GetPrefab("TorusTest");
    Engine::Prefab* prf2 = m_cache->GetPrefab("PawnObject");
    Engine::Prefab* prf3 = m_cache->GetPrefab("TerrainTest");


    assert (ptex != nullptr);
    assert (prf1 != nullptr);
    assert (prf2 != nullptr);
    assert (prf3 != nullptr);


    // Load texture to GPU
    //assert (ptex->Ready());
    //ptex->GLPush();
    //assert (ptex->GLReady());

    // Setup material properties
    //pModel->GetMaterial()->ShaderParameters()->SetTexValue("diff1map", ptex);

    // ECS setup
    auto torus = m_core->ECS()->CreateEntity(prf1);
    auto player = m_core->ECS()->CreateEntity(prf2);
    //auto terr = m_core->ECS()->CreateEntity(prf3);
    m_core->ECS()->CreateProcess<TestProc>();
    m_core->ECS()->CreateProcess<Engine::Processes::WobbleProcess>();
    m_core->ECS()->CreateProcess<Engine::Processes::ControllerProcess>();
    m_core->ECS()->CreateProcess<Engine::Processes::MovementProcess>();

    // Setup main scene camera - Default fallback if there are not camera components in the scene
    m_camera = std::make_unique<Engine::Camera>(30, 1.7777);
    m_camera->GetTransform().Translate(Vec3(0, 0, -10));

    // Tmp - Lower ground plane test
    //terr->Components().GetFirst<Engine::Components::TransformComponent>()->GetTransform().SetTranslation(Vec3(0,-3,0));
    //terr->Components().GetFirst<Engine::Components::TransformComponent>()->GetTransform().SetScale(5);
    
    auto ctrl = player->Components().Add<Engine::Components::PlayerControllerComponent>();
    ctrl->CaptureComponent(player->Components().GetFirst<Engine::Components::MovementComponent>());

    // New terrain component testing
    auto newTerr = m_core->ECS()->CreateEntity();
    newTerr->Components().Add<Engine::Components::TerrainComponent>();
    newTerr->Components().GetFirst<Engine::Components::TerrainComponent>()->SetTileSize(1.0f);
    newTerr->Components().GetFirst<Engine::Components::TerrainComponent>()->SetRows(64);
    newTerr->Components().GetFirst<Engine::Components::TerrainComponent>()->SetColumns(64);
    newTerr->Components().GetFirst<Engine::Components::TerrainComponent>()->SetMaterial(m_cache->GetMaterial("TerrainMaterial"));

    // Tmp move torus up to test shadows
    torus->Components().GetFirst<Engine::Components::TransformComponent>()->GetTransform().Translate(Vec3(0,5,0));
}

Engine::Camera* TestScene::Cam()
{
    return m_camera.get();
}

void TestScene::Free()
{
    m_cache->Free();
}

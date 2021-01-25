#include "testscene.hpp"
#include "engine/processes/wobbleprocess.hpp"
#include "engine/processes/controllerprocess.hpp"
#include "engine/processes/playercontrollerprocess.hpp"
#include "engine/processes/movementprocess.hpp"
#include "engine/components/playercontrollercomponent.hpp"
#include "engine/components/movementcomponent.hpp"
#include "engine/level.hpp"

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

    // ECS setup
    m_core->ECS()->CreateProcess<Engine::Processes::WobbleProcess>();
    m_core->ECS()->CreateProcess<Engine::Processes::ControllerProcess>();
    m_core->ECS()->CreateProcess<Engine::Processes::MovementProcess>();
    m_core->ECS()->CreateProcess<Engine::Processes::PlayerControllerProcess>();

    // Setup main scene camera - Default fallback if there are not camera components in the scene
    m_camera = std::make_unique<Engine::Camera>(30, 1.7777);
    m_camera->GetTransform().Translate(Vec3(0, 0, -10));

    // Load Level
    auto level = std::make_unique<Engine::Level>(m_cache.get(), m_core->ECS());
    level->AddObjectsFromManifest("/home/dantheman/local/dev/games/labour-day/labour-day/content/levels/test-01.json");
}

Engine::Camera* TestScene::Cam()
{
    return m_camera.get();
}

void TestScene::Free()
{
    m_cache->Free();
}

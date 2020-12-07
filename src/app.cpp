#include "app.hpp"
#include "engine/debugging.hpp"
#include "engine/inputmanager.hpp"
#include "engine/components/modelcomponent.hpp"

bool App::Initialize()
{
    assert (m_core == nullptr && "Engine core is already initialized !");

    Engine::EngineCoreSettings settings = Engine::EngineCoreSettings();
    settings.m_windowWidth = 1280;
    settings.m_windowHeight = 720;

    m_core = std::make_unique<Engine::EngineCore>();
    if(!m_core->Initialize(settings))
    {
        return false;
    }

    m_testScene = std::make_unique<TestScene>();
    m_testScene->Initialize(m_core.get());
    m_core->Renderer()->SetCamera(m_testScene->Cam());

    return true;
}

void App::Run()
{
    assert (m_core != nullptr);
    
    while(m_core->MainWindowActive() && !Engine::InputManager::Instance().CheckKey(KEY_ESCAPE))
    {
        m_core->IncrementTime();
        Engine::InputManager::Instance().Poll();
        UpdateGame(m_core->GetDeltaTime());
        UpdateUI();
        DrawGame();
    }
}

void App::Exit()
{
    assert (m_core != nullptr);
    m_testScene->Free();
    
    m_core->Terminate();
    m_core.reset(nullptr);
    m_core = nullptr;
}

Engine::EngineCore* App::Engine()
{
    return m_core.get();
}

void App::UpdateGame(const double deltaTime)
{
    assert (m_testScene != nullptr);
    m_core->ECS()->Update(deltaTime);
}

void App::UpdateUI()
{
    assert (Engine() != nullptr);
    assert (Engine()->IMGui() != nullptr);

    Engine()->IMGui()->Update();
}

void App::DrawGame()
{
    assert (m_core != nullptr);
    m_core->ClearMainWindow();

    // Old common rendering
    m_core->RedrawMainWindow();

    // Component Based Rendering
    std::vector<Engine::Entity*> rEntities;
    m_core->ECS()->AssetsByComponent<Engine::Components::ModelComponent>(rEntities);
    for (auto &entity : rEntities)
    {
        auto cmodel = entity->Components().Get<Engine::Components::ModelComponent>();
        assert (cmodel != nullptr);
        
        m_core->Renderer()->DrawModel(cmodel);
        m_core->Renderer()->DrawModelWire(cmodel);
        
    }

    // Draw UI layer to the screen
    DrawUI();
    
    // Swap buffers
    m_core->PresentMainWindow();
}

void App::DrawUI()
{
    assert (Engine() != nullptr);
    assert (Engine()->IMGui() != nullptr);

    Engine()->IMGui()->Render();
}
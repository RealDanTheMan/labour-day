#include "app.hpp"
#include "engine/debugging.hpp"
#include "engine/inputmanager.hpp"
#include "engine/components/modelcomponent.hpp"
#include "engine/components/cameracomponent.hpp"

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

    // Initialise main debug overlay
    m_overlay = std::make_unique<Engine::DebugOverlay>(m_core.get());
    m_core->IMGui()->AddPanel(m_overlay.get());

    // Initialise test (debug) scene
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
        m_core->FPS()->Sample();
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

    // Use component camera if one exists
    std::vector<Engine::Entity*> cams;
    m_core->ECS()->AssetsByComponent<Engine::Components::CameraComponent>(cams);
    if(cams.size() > 0)
    {
        Engine::Components::CameraComponent* cCam = cams[0]->Components().GetFirst<Engine::Components::CameraComponent>();
        if(cCam->IsActive())
        {
            m_core->Renderer()->SetCamera(cCam->CameraHandle());
        }
    }

    // Old common rendering
    m_core->RedrawMainWindow();

    // Ecs based drawing
    m_core->Renderer()->DrawModelComponents(m_core->ECS());
    m_core->Renderer()->DrawTransformComponents(m_core->ECS());

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
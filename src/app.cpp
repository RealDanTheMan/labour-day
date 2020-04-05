#include "app.hpp"
#include "engine/debugging.hpp"
#include "engine/inputmanager.hpp"

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
    m_core->Renderer()->AddToQueue(m_testScene->TestTriangle());

    return true;
}

void App::Run()
{
    assert (m_core != nullptr);
    
    while(m_core->MainWindowActive() && !Engine::InputManager::Instance().CheckKey(KEY_ESCAPE))
    {
        Engine::InputManager::Instance().Poll();
        UpdateGame();
        DrawGame();
    }
    
}

void App::Exit()
{
    assert (m_core != nullptr);
    
    m_core->Terminate();
    m_core.reset(nullptr);
    m_core = nullptr;
}

Engine::EngineCore* App::Engine()
{
    return m_core.get();
}

void App::UpdateGame()
{
    assert (m_testScene != nullptr);
    m_testScene->Update();
}

void App::DrawGame()
{
    assert (m_core != nullptr);
    m_core->ClearMainWindow();
    m_core->RedrawMainWindow();
}
#include "app.hpp"
#include "engine/debugging.hpp"

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

    return true;
}

void App::Run()
{
    assert (m_core != nullptr);
    
    while(m_core->MainWindowActive())
    {
        m_core->RedrawMainWindow();
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
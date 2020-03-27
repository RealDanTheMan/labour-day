#include "enginecore.hpp"
#include "debugging.hpp"

using namespace Engine;

EngineCore::EngineCore():
m_glew(nullptr),
m_glfw(nullptr),
m_mainWin(nullptr)
{
}

bool EngineCore::Initialize()
{
    assert (m_glew == nullptr);
    assert (m_glfw == nullptr);
    
    m_glfw = std::make_unique<GLFWInterface>();
    if(!m_glfw->Initialize())
    {
        D_ERR("Failed to initialize GLFW context !");
        return false;
    }

    m_mainWin = std::make_unique<Window>();
    if(m_mainWin == nullptr || m_mainWin->GetHandle() == nullptr)
    {
        D_ERR("Failed to initialize GLFW window !");
        return false;
    }

    glfwMakeContextCurrent(m_mainWin->GetHandle());
    m_glew = std::make_unique<GLEWInterface>();
    if(!m_glew->Initialize())
    {
        D_ERR("Failed to initialize GLEW context !");
        return false;
    }

    m_renderer = std::make_unique<CommonRenderer>();
    return true;
}

bool EngineCore::Initialize(const EngineCoreSettings &settings)
{
    assert (m_glfw == nullptr);
    m_glfw = std::make_unique<GLFWInterface>();

    if(!m_glfw->Initialize())
    {
        return false;
    }

    m_mainWin = std::make_unique<Window>(settings.m_windowWidth, settings.m_windowHeight);
    if(m_mainWin == nullptr || m_mainWin->GetHandle() == nullptr)
    {
        D_ERR("Failed to initialize GLFW window !");
        return false;
    }

    glfwMakeContextCurrent(m_mainWin->GetHandle());
    m_glew = std::make_unique<GLEWInterface>();
    if(!m_glew->Initialize())
    {
        D_ERR("Failed to initialize GLEW context !");
        return false;
    }

    m_renderer = std::make_unique<CommonRenderer>();    
    return true;
}

void EngineCore::Terminate()
{
    assert (m_glfw != nullptr);
    assert (m_glfw->Initialized());

    m_glfw->Terminate();
    m_glfw.release();
    m_glfw = nullptr;
}

void EngineCore::RedrawMainWindow()
{
    assert (m_glfw != nullptr);
    assert (m_glfw->Initialized());
    assert (m_mainWin != nullptr);
    assert (m_mainWin->Ready());
    assert (m_renderer != nullptr);

    glfwPollEvents();
    m_renderer->DrawRenderables();
    glfwSwapBuffers(m_mainWin->GetHandle());
}

const bool EngineCore::MainWindowActive() const
{
    assert (m_glfw != nullptr);
    assert (m_glfw->Initialized());
    assert (m_mainWin != nullptr);

    return m_mainWin->Ready();
}

CommonRenderer* EngineCore::Renderer()
{
    return m_renderer.get();
}
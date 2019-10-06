#include "enginecore.hpp"
#include "assert.h"

using namespace Engine;

EngineCore::EngineCore():
m_glfw(nullptr),
m_mainWin(nullptr)
{
}

bool EngineCore::Initialize()
{
    assert (m_glfw == nullptr);
    m_glfw = std::make_unique<GLFWInterface>();

    if(!m_glfw->Initialize())
    {
        return false;
    }

    m_mainWin = std::make_unique<Window>();


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
        return false;
    }
    
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

    glfwPollEvents();
    glfwSwapBuffers(m_mainWin->GetHandle());
}

const bool EngineCore::MainWindowActive() const
{
    assert (m_glfw != nullptr);
    assert (m_glfw->Initialized());
    assert (m_mainWin != nullptr);

    return m_mainWin->Ready();
}
#include "enginecore.hpp"
#include "assert.h"

using namespace Engine;

EngineCore::EngineCore():
m_glfw(nullptr)
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
#include "gfx.hpp"
#include "debugging.hpp"

using namespace Engine;

bool Gfx::Init()
{
    m_glew = std::make_unique<GLEWInterface>();
    if(!m_glew->Initialize())
    {
        D_ERR("Failed to initialize GLEW context !");
        return false;
    }

    m_baseShaders = std::make_unique<RuntimeShaders>();
    m_baseShaders->Init();
    if(!m_baseShaders->Ready())
    {
        D_ERR("Failed to initialize base runtime shaders !");
        return false;
    }

    return true;
}

void Gfx::Free()
{
    if(m_glew != nullptr)
    {
        m_glew.reset();
        m_glew = nullptr;
    }

    if(m_baseShaders != nullptr)
    {
        m_baseShaders->Free();
        m_baseShaders.reset();
        m_baseShaders = nullptr;
    }
}

const RuntimeShaders* Gfx::BaseShaders()
{
    return m_baseShaders.get();
}
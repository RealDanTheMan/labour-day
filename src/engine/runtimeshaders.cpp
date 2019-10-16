#include "runtimeshaders.hpp"
#include "debugging.hpp"

using namespace Engine;

void RuntimeShaders::Init()
{
    std::unique_ptr<ShaderSource> flatWhiteVS = std::make_unique<ShaderSource>(FLAT_WHITE_VERT_SRC, ShaderSource::ShaderSourceType::Vertex);
    std::unique_ptr<ShaderSource> flatWhitePS = std::make_unique<ShaderSource>(FLAT_WHITE_PIX_SRC, ShaderSource::ShaderSourceType::Pixel);
    flatWhiteVS->Compile();
    flatWhitePS->Compile();

    D_MSG(flatWhiteVS->GetLog());
    D_MSG(flatWhitePS->GetLog());

    assert (flatWhiteVS->Compiled());
    assert (flatWhitePS->Compiled());

    m_flatWhite = std::make_unique<ShaderProg>(*flatWhiteVS.get(), *flatWhitePS.get());
    assert (m_flatWhite->Ready());

    flatWhiteVS->Free();
    flatWhitePS->Free();
}

void RuntimeShaders::Free()
{
    if(m_flatWhite != nullptr)
    {
        m_flatWhite->Free();
        m_flatWhite.reset();
    }
}

const bool RuntimeShaders::Ready() const 
{
    if(m_flatWhite == nullptr || !m_flatWhite->Ready())
    {
        return true;
    }

    return true;
}

const ShaderProg* RuntimeShaders::FlatWhite() const
{
    return m_flatWhite.get();
}
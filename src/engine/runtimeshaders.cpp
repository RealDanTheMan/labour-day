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

    std::unique_ptr<ShaderSource> diffVS = std::make_unique<ShaderSource>(DIFF_VERT_SRC, ShaderSource::ShaderSourceType::Vertex);
    std::unique_ptr<ShaderSource> diffPS = std::make_unique<ShaderSource>(DIFF_PIX_SRC, ShaderSource::ShaderSourceType::Pixel);
    diffVS->Compile();
    diffPS->Compile();

    D_MSG(diffVS->GetLog());
    D_MSG(diffPS->GetLog());

    assert (diffVS->Compiled());
    assert (diffPS->Compiled());

    m_diff = std::make_unique<ShaderProg>(*diffVS.get(), *diffPS.get());
    assert (m_diff->Ready());

    diffVS->Free();
    diffPS->Free();
}

void RuntimeShaders::Free()
{
    if(m_flatWhite != nullptr)
    {
        m_flatWhite->Free();
        m_flatWhite.reset();
    }

    if(m_diff != nullptr)
    {
        m_diff->Free();
        m_diff.reset();
    }
}

const bool RuntimeShaders::Ready() const 
{
    if(m_flatWhite == nullptr || !m_flatWhite->Ready())
    {
        return false;
    }
    if(m_diff == nullptr || !m_diff->Ready())
    {
        return false;
    }

    return true;
}

const ShaderProg* RuntimeShaders::FlatWhite() const
{
    return m_flatWhite.get();
}

const ShaderProg* RuntimeShaders::Diff() const
{
    return m_diff.get();
}
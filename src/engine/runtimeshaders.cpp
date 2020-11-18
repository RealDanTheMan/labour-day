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

    std::unique_ptr<ShaderSource> diff1VS = std::make_unique<ShaderSource>(DIFF1_VERT_SRC, ShaderSource::ShaderSourceType::Vertex);
    std::unique_ptr<ShaderSource> diff1PS = std::make_unique<ShaderSource>(DIFF1_PIX_SRC, ShaderSource::ShaderSourceType::Pixel);
    diff1VS->Compile();
    diff1PS->Compile();

    D_MSG(diff1VS->GetLog());
    D_MSG(diff1PS->GetLog());

    assert (diff1VS->Compiled());
    assert (diff1PS->Compiled());

    m_diff1 = std::make_unique<ShaderProg>(*diff1VS.get(), *diff1PS.get());
    assert (m_diff1->Ready());

    diff1VS->Free();
    diff1PS->Free();
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
    if(m_diff1 == nullptr || !m_diff1->Ready())
    {
        return false;
    }

    return true;
}

const ShaderProg* const RuntimeShaders::FlatWhite() const
{
    return m_flatWhite.get();
}

const ShaderProg* const RuntimeShaders::Diff() const
{
    return m_diff.get();
}

const ShaderProg* const RuntimeShaders::Diff1() const
{
    return m_diff1.get();
}

const ShaderProg* const RuntimeShaders::GetByName(const std::string &name) const
{
    // Not the best but good enough to get the shader pipe off the ground 
    if(name == "flatwhite")
    {
        return FlatWhite();
    }

    if(name == "diff")
    {
        return Diff();
    }

    if(name == "diff1")
    {
        return Diff1();
    }

    return nullptr;
}
#include "texsampler.hpp"
#include "debugging.hpp"

using namespace Engine;

void TexSampler::Init()
{
    assert (m_glHandle == 0);
    glCreateSamplers(1, &m_glHandle);
    assert (m_glHandle != 0);
}

void TexSampler::Free()
{
    glDeleteSamplers(1, &m_glHandle);
    m_glHandle = 0;
}

bool TexSampler::Ready() const
{
    if(m_glHandle == 0)
    {
        return false;
    }

    return true;
}

const GLuint TexSampler::Handle() const
{
    return m_glHandle;
}
#include "shadowmaprenderer.hpp"

using namespace Engine;

void ShadowmapRenderer::Init(const ShadowmapSettings &settings) 
{
    assert (!Ready());

    m_fb = std::make_unique<ShadowFrameBuffer>(settings.m_resx, settings.m_resy);
    m_fb->Init();

    if(m_fb->Ready())
    {
        m_ready = true;
    }
}

bool ShadowmapRenderer::Ready() const
{
    return m_ready;
}
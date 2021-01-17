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

void ShadowmapRenderer::RenderShadows(std::vector<const ModelInstance*> &instances) const
{
    assert (Ready());
    assert (m_fb->Ready());

    // Bind frame buffer and setup viewport
    glBindFramebuffer(GL_FRAMEBUFFER, m_fb->FramebufferHandle());
    glViewport(0, 0, m_fb->Width(), m_fb->Height());

    // Clear current contents of the shadow buffer
    glClearDepth(1.0f);
    glClear(GL_DEPTH_TEST);

    // Draw into the shadow buffer
    glEnable(GL_POLYGON_OFFSET_FILL);
    glPolygonOffset(2.0f, 4.0f);
    
    // Draw geometry into shadow map
    for(auto &instance : instances)
    {
        DrawIntoShadowMap(instance);
    }

    // Unbind the buffer after work is done
    glDisable(GL_POLYGON_OFFSET_FILL);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void ShadowmapRenderer::DrawIntoShadowMap(const ModelInstance *instance) const
{
    // TODO: Shadow draw call
}
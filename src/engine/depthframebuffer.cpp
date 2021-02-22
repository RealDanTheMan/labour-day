#include "depthframebuffer.hpp"

using namespace Engine;

DepthFramebuffer::DepthFramebuffer():
m_width(2048U),
m_height(2048U),
m_ready(false),
m_depthMap(0),
m_frameBuffer(0)
{

}

DepthFramebuffer::DepthFramebuffer(const uint32_t w, const uint32_t h):
m_width(w),
m_height(h),
m_ready(false),
m_depthMap(0),
m_frameBuffer(0)
{

}

void DepthFramebuffer::Init()
{
    assert (!Ready());
    assert (Width() > 0);
    assert (Height() > 0);

    // Generate and bind texture object for this frame buffer
    glGenTextures(1, &m_depthMap);
    glBindTexture(GL_TEXTURE_2D, m_depthMap);

    // Generate shadow map texture
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT24, Width(), Height(), 0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr );


    // Configure shadow map texture parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_REF_TO_TEXTURE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL);

    // Unbind texture
    glBindTexture(GL_TEXTURE_2D, 0);

    // Generate frame buffer object & attach texture to it
    glGenFramebuffers(1, &m_frameBuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, m_frameBuffer);
    glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, m_depthMap, 0);
    glDrawBuffer(GL_NONE);
    glReadBuffer(GL_NONE);

    // Unbind frame buffer
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    if(m_depthMap != 0 && m_frameBuffer != 0)
    {
        m_ready = true;
    }
}

bool DepthFramebuffer::Ready() const
{
    return m_ready;
}

uint32_t DepthFramebuffer::Width() const
{
    return m_width;
}

uint32_t DepthFramebuffer::Height() const
{
    return m_height;
}

const GLuint DepthFramebuffer::FramebufferHandle() const
{
    return m_frameBuffer;
}
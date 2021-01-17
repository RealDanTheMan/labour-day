#include "shadowmaprenderer.hpp"
#include "glm/gtx/transform.hpp"

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

    CompileShader();
}

bool ShadowmapRenderer::Ready() const
{
    if(m_shader != nullptr && m_shader->Ready() && m_ready)
    {
        return true;
    }

    return false;
}

void ShadowmapRenderer::RenderShadows(std::vector<const ModelInstance*> &instances, const Vec3 &lightDir) const
{
    assert (Ready());
    assert (m_fb->Ready());
    assert (m_fb->Width() > 0);
    assert (m_fb->Height() > 0);

    // Bind frame buffer and setup viewport
    glBindFramebuffer(GL_FRAMEBUFFER, m_fb->FramebufferHandle());
    glViewport(0, 0, m_fb->Width(), m_fb->Height());

    // Guard against corrupted shadow frame buffer
    assert (glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE);

    // Clear current contents of the shadow buffer
    glClearDepth(1.0f);
    glClear(GL_DEPTH_BUFFER_BIT);

    // Draw into the shadow buffer
    glEnable(GL_POLYGON_OFFSET_FILL);
    glPolygonOffset(2.0f, 4.0f);
    
    // Draw geometry into shadow map
    for(auto &instance : instances)
    {
        DrawIntoShadowMap(instance, lightDir);
    }

    // Unbind the buffer after work is done
    glDisable(GL_POLYGON_OFFSET_FILL);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void ShadowmapRenderer::DrawIntoShadowMap(const ModelInstance *instance, const Vec3 &lightDir) const
{
    assert (Ready());
    assert (instance != nullptr);
    assert (instance->GetModel() != nullptr);
    assert (instance->GetModel()->GetRenderable() != nullptr);
    assert (instance->GetModel()->GetRenderable()->Ready());

    auto renderable = instance->GetModel()->GetRenderable();

    // Calculate model instance transform
    Transform tr = Transform(instance->GetModel()->GetTransform());
    tr.TransformBy(instance->GetTransform());

    // Calculate light view matrix
    const Vec3 eye = tr.Translation() + (Vec3(1000.0f,1000.0f,1000.0f) * lightDir);
    const Vec3 target = tr.Translation();
    const Mat4 view = glm::lookAt(eye, target, Vec3(0.0f,1.0f,0.0f));

    // Push shader params
    glUseProgram(m_shader->GetHandle());
    GLint svViewLoc = glGetUniformLocation(m_shader->GetHandle(), SV_VIEW);
    GLint svProjLoc = glGetUniformLocation(m_shader->GetHandle(), SV_PROJECTION);
    GLint svModelLoc = glGetUniformLocation(m_shader->GetHandle(), SV_MODEL);

    assert (svViewLoc != -1);
    assert (svProjLoc != -1);
    assert (svModelLoc != -1);

    glUniformMatrix4fv(svViewLoc, 1, GL_FALSE, &view[0][0]);
    //glUniformMatrix4fv(svProjLoc, 1, GL_FALSE, &m_activeCam->Projection()[0][0]);
    glUniformMatrix4fv(svModelLoc, 1, GL_FALSE, &tr.Matrix()[0][0]);

    // Draw into the shadow buffer
    glBindVertexArray(renderable->VertexAttributes());
    glEnableVertexAttribArray(0);
    glDrawElements(GL_TRIANGLES, renderable->IndexCount(), GL_UNSIGNED_INT, 0);

    // Clear states
    glUseProgram(0);
    glDisableVertexAttribArray(0);
    glBindVertexArray(0);
}

void ShadowmapRenderer::CompileShader()
{
    // Shadow pass shader
    std::unique_ptr<ShaderSource> shadowPassVS = std::make_unique<ShaderSource>(SHADOWPASS_VERT_SRC, ShaderSource::ShaderSourceType::Vertex);
    std::unique_ptr<ShaderSource> shadowPassPS = std::make_unique<ShaderSource>(SHADOWPASS_PIX_SRC, ShaderSource::ShaderSourceType::Pixel);
    shadowPassVS->Compile();
    shadowPassPS->Compile();

    D_MSG(shadowPassVS->GetLog());
    D_MSG(shadowPassPS->GetLog());

    assert (shadowPassVS->Compiled());
    assert (shadowPassPS->Compiled());

    m_shader = std::make_unique<ShaderProg>(*shadowPassVS.get(), *shadowPassPS.get());
    assert (m_shader->Ready());

    shadowPassVS->Free();
    shadowPassPS->Free();
}
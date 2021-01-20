#include "shadowmaprenderer.hpp"
#include "glm/gtx/transform.hpp"

using namespace Engine;

const Vec3 ShadowmapRenderer::UP_AXIS0 = Vec3(0,1,0);
const Vec3 ShadowmapRenderer::UP_AXIS1 = Vec3(0,0,1);
const float ShadowmapRenderer::DEF_DIST = 50.0f;

void ShadowmapRenderer::Init(const ShadowmapSettings &settings) 
{
    assert (!Ready());

    // Set all matrices to identity
    m_lightView = Transform::IdentityMatrix();
    m_lightProj = Transform::IdentityMatrix();
    m_scaleBias = Transform::IdentityMatrix();
    m_shadowProj = Transform::IdentityMatrix();

    // Store shadow settings
    // For now shadow settings are static for the lifetime of the renderer
    m_settings = ShadowmapSettings(settings);

    // Configure shadow frame buffer
    m_fb = std::make_unique<ShadowFrameBuffer>(settings.m_resx, settings.m_resy);
    m_fb->Init();

    if(m_fb->Ready())
    {
        m_ready = true;
    }

    // Setup shadow depth vertex shader
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

void ShadowmapRenderer::RenderShadows(std::vector<const ModelInstance*> &instances, const Vec3 &lightDir)
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
    ComputeMatrices(lightDir);
    for(auto &instance : instances)
    {
        DrawIntoShadowMap(instance, lightDir);
    }

    // Unbind the buffer after work is done
    glDisable(GL_POLYGON_OFFSET_FILL);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void ShadowmapRenderer::DrawIntoShadowMap(const ModelInstance *instance, const Vec3 &lightDir)
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

    // Push shader params
    glUseProgram(m_shader->GetHandle());
    GLint svViewLoc = glGetUniformLocation(m_shader->GetHandle(), SV_VIEW);
    GLint svProjLoc = glGetUniformLocation(m_shader->GetHandle(), SV_PROJECTION);
    GLint svModelLoc = glGetUniformLocation(m_shader->GetHandle(), SV_MODEL);

    assert (svViewLoc != -1);
    assert (svProjLoc != -1);
    assert (svModelLoc != -1);

    glUniformMatrix4fv(svViewLoc, 1, GL_FALSE, &m_lightView[0][0]);
    glUniformMatrix4fv(svProjLoc, 1, GL_FALSE, &m_lightProj[0][0]);
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

void ShadowmapRenderer::ComputeMatrices(const Vec3 &lightDir)
{
    // Compute light view transoform matrix
    const Vec3 eye = (Vec3(DEF_DIST, DEF_DIST, DEF_DIST) * lightDir);
    if(glm::abs(glm::dot(glm::normalize(eye), UP_AXIS0)) != 1)
    {
        // Use default up axis if light vec is not parallel to default up axis
        m_lightView = glm::lookAt(eye, Vec3(0,0,0), UP_AXIS0);
    }
    else
    {
        // Use alternative up axis if light vec is parallel to default up axis
        m_lightView = glm::lookAt(eye, Vec3(0,0,0), UP_AXIS1);
    }

    // Cmpute light projection transform matrix
    assert (GetSettings().m_minDistance > 0.0f);
    assert (GetSettings().m_maxDistance > 0.0f);
    m_lightProj = Mat4(glm::frustum(-1.0f, 1.0f, -1.0f, 1.0f, 1.0f, GetSettings().m_maxDistance));

    // Compute shadow scale bias matrix
    // Do we ever need to change this in the future - perhaps make it static ?
    const float scale = 0.5f;
    m_scaleBias = Mat4(
        Vec4(scale, 0.0f, 0.0f, 0.0f),
        Vec4(0.0f, scale, 0.0f, 0.0f),
        Vec4(0.0f, 0.0f, scale, 0.0f),
        Vec4(scale, scale, scale, 1.0f)
    );

    // Compute shadow projection matrix
    m_shadowProj = m_scaleBias * m_lightProj * m_lightView;
}

const ShadowmapSettings & ShadowmapRenderer::GetSettings() const
{
    return m_settings;
}

const Mat4 & ShadowmapRenderer::GetShadowProjMatrix() const
{
    return m_shadowProj;
}

const GLuint ShadowmapRenderer::GetShadowMapHandle() const 
{
    assert (m_fb != nullptr);
    return m_fb->ShadowMapHandle();
}
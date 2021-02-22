#include "commonrenderer.hpp"
#include "meshgen.hpp"
#include "components/lightcomponent.hpp"

using namespace Engine;

CommonRenderer::CommonRenderer(const RuntimeShaders * const rtShaders, const RenderSettings& settings):
m_runtimeShaders(rtShaders),
m_settings(settings)
{
    assert (rtShaders != nullptr);
    assert (rtShaders->Ready());

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LINE_SMOOTH);
    glEnable(GL_BLEND);
    glEnable(GL_MULTISAMPLE);
    glDisable(GL_DITHER);

    // Init default box locator
    std::unique_ptr<Mesh> msh = MeshGen::Cube(0.1f);
    m_locator = std::make_unique<Renderable>();
    m_locator->Init(*msh);
    m_locator->BindShader(rtShaders->FlatWhite());

    // Init default line gizom
    std::unique_ptr<Mesh> line = MeshGen::Line(Vec3(0,0,0), Vec3(0,10,0));
    m_line = std::make_unique<DynamicRenderable>();
    m_line->Init(*line);
    m_line->BindShader(rtShaders->FlatWhite());

    // Fallback light setup
    m_defaultLight.SetDirection(glm::normalize(Vec3(0.5,-1,0.5)));
    m_defaultLight.SetIntensity(1.0f);

    // Setup shadow rendering
    ShadowmapSettings shadowSettings;
    shadowSettings.m_resx = 4096;
    shadowSettings.m_resy = 4096;
    shadowSettings.m_minDistance = 0.001;
    shadowSettings.m_maxDistance = 100;
    shadowSettings.m_biasOffset = 0.0f;
    m_shadowRenderer = std::make_unique<ShadowmapRenderer>();
    m_shadowRenderer->Init(shadowSettings);

    // Last frame depth buffer
    m_zbuffer = std::make_unique<DepthFramebuffer>(settings.m_resx, settings.m_resy);
    m_zbuffer->Init();
}


void CommonRenderer::Clear() const
{
    glClearColor(0, 0, 1, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // TODO: Perhaps clear the shadowmap frame buffer here as well ?!
}

void CommonRenderer::SwapDepthBuffers()
{
    assert (m_zbuffer != nullptr);
    
    glBindFramebuffer(GL_READ_FRAMEBUFFER, 0);
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, GetLastZBuffer()->FramebufferHandle());
    glBlitFramebuffer(
            0, 0, 
            GetRenderSettings().m_resx, 
            GetRenderSettings().m_resy, 
            0, 0,
            GetLastZBuffer()->Width(), 
            GetLastZBuffer()->Height(),
            GL_DEPTH_BUFFER_BIT,
            GL_NEAREST
    );

    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
    glBindFramebuffer(GL_READ_FRAMEBUFFER, 0);
}

[[deprecated]]
void CommonRenderer::DrawRenderables() const
{
    for (uint32_t i=0; i < m_queue.size(); i++)
    {
        DrawRenderable(m_queue[i], nullptr, DrawMode::Fill, nullptr);
    }
}

void CommonRenderer::DrawRenderable(const Renderable *renderable, const Transform *tr, const DrawMode mode, const Material * const mat) const
{
    assert (renderable != nullptr);
    assert (m_runtimeShaders != nullptr);
    assert (renderable->Ready());
    assert (m_runtimeShaders->Ready());

    switch (mode)
    {
        case DrawMode::Wireframe:
            glUseProgram(m_runtimeShaders->FlatWhite()->GetHandle());
            PushUniformShaderParams(m_runtimeShaders->FlatWhite(), tr);
            break;
        case DrawMode::Line:
            glUseProgram(m_runtimeShaders->FlatWhite()->GetHandle());
            PushUniformShaderParams(m_runtimeShaders->FlatWhite(), tr);
            break;
        default:
            glUseProgram(renderable->GetShader()->GetHandle());
            PushUniformShaderParams(renderable->GetShader(), tr);
            PushLightShaderParams(renderable->GetShader());
            PushShadowShaderParams(renderable->GetShader());
            if(mat != nullptr)
            {
                PushMaterialShaderParams(*renderable->GetShader(), *mat);
                BindMaterialTextures(*renderable->GetShader(), *mat);
            }
            break;
    }

    glViewport(0, 0, GetRenderSettings().m_resx,  GetRenderSettings().m_resy);
    glBindVertexArray(renderable->VertexAttributes());
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);

    switch (mode)
    {
        case DrawMode::Wireframe:
            glDepthMask(GL_FALSE);
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            glDrawElements(GL_TRIANGLES, renderable->IndexCount(), GL_UNSIGNED_INT, 0);
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            glDepthMask(GL_TRUE);
            break;
        case DrawMode::Line:
            //  Remap depth reange since we want to make sure the lines are always on top
            glDepthRange(0.0, 0.001);
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            glDrawElements(GL_LINES, renderable->IndexCount(), GL_UNSIGNED_INT, 0);
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            glDepthRange(0.0, 1);
        default:
            glDrawElements(GL_TRIANGLES, renderable->IndexCount(), GL_UNSIGNED_INT, 0);
            break;
    }

    if(mat != nullptr)
    {
        UnbindMaterialTextures(*renderable->GetShader(), *mat);
    }

    glUseProgram(0);
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(2);
    glBindVertexArray(0);
}

void CommonRenderer::DrawModelInstance(const ModelInstance *instance) const
{
    assert (instance != nullptr);
    assert (instance->GetModel() != nullptr);
    assert (instance->GetModel()->GetRenderable() != nullptr);
    assert (instance->GetModel()->GetRenderable()->Ready());

    const Material *mat = instance->GetModel()->GetMaterial();
    const Renderable *h = instance->GetModel()->GetRenderable();

    // Apply model instance transform
    Transform tr = Transform(instance->GetModel()->GetTransform());
    tr.TransformBy(instance->GetTransform());
    
    // Main pass draw call
    DrawRenderable(h, &tr, DrawMode::Fill, mat);

    // Wireframe draw call
    if(GetRenderSettings().m_wireframe)
    {
        DrawRenderable(h, &tr, DrawMode::Wireframe, nullptr);
    }
}

void CommonRenderer::DrawLocator(const Transform * tr) const
{
    assert (tr != nullptr);
    assert (m_locator != nullptr);

    DrawRenderable(m_locator.get(), tr, DrawMode::Wireframe, nullptr);
}

void CommonRenderer::DrawModelComponents(ECSSys *ecs) const
{
    assert (ecs != nullptr);

    // Fetch all entities that contain model components
    std::vector<Components::ModelComponent*> modelComs = ecs->GetAllComponents<Components::ModelComponent>();
    std::vector<const ModelInstance*> instances;

    // Resolve all model instances
    for (auto &com : modelComs)
    {
        instances.push_back(com->GetModelInstance());
    }

    // Shadow render pass for model components
    if(GetRenderSettings().m_shadows)
    {
        assert (m_shadowRenderer != nullptr);
        assert (GetMainLight() != nullptr);
        
        m_shadowRenderer->ClearShadows();
        m_shadowRenderer->RenderShadows(instances, GetCamera()->View()[3], -GetMainLight()->GetDirection());
    }
    else if(!GetRenderSettings().m_shadows && m_shadowRenderer != nullptr)
    {
        // If we disable shadows after they were draw at least once 
        // we have to clear the shadow map at least or shadow will be stuck on screen
        // at last recorded position
        m_shadowRenderer->ClearShadows();
    }

    // Main scene render pass for model components
    for (auto &instance : instances)
    {
        DrawModelInstance(instance);
    }
}

void CommonRenderer::DrawTransformComponents(ECSSys *ecs) const
{
    // Fetch all entities that contain transform components
    std::vector<Engine::Entity*> entities;
    ecs->AssetsByComponent<Engine::Components::TransformComponent>(entities);

    // Draw locator for each transform component
    for (auto &entity : entities)
    {
        auto cTransforms = entity->Components().GetAll<Engine::Components::TransformComponent>();
        for(auto &cTransform : cTransforms)
        {
            DrawLocator(&cTransform->GetTransform());
        }
    }
}

void CommonRenderer::DrawLightComponents(ECSSys * ecs) const
{
    std::vector<Engine::Entity*> entities;
    ecs->AssetsByComponent<Engine::Components::LightComponent>(entities);

    // Draw locator for each transform component
    for (auto &entity : entities)
    {
        auto cLights = entity->Components().GetAll<Engine::Components::LightComponent>();
        for(auto &cLight : cLights)
        {
            DrawLocator(&cLight->GetTransform());
        }
    }
}

void CommonRenderer::ClearQueue()
{
    m_queue.clear();
}

void CommonRenderer::AddToQueue(const Renderable *renderable)
{
    m_queue.push_back(renderable);
}

void CommonRenderer::SetCamera(const Camera *cam)
{
    m_activeCam = cam;
}

void CommonRenderer::SetRenderSettings(const RenderSettings &settings)
{
    m_settings = RenderSettings(settings);
}

const Camera * const CommonRenderer::GetCamera() const
{
    return m_activeCam;
}

const RenderSettings & CommonRenderer::GetRenderSettings() const
{
    return m_settings;
}

LightsCache & CommonRenderer::GetLightsCache() 
{
    return m_lightsCache;
}

const DirectionalLight * CommonRenderer::GetMainLight() const
{
    // Fetch main light
    // If sunlight light has not been set in light cache then use fallback (engine) one
    const DirectionalLight * pMainLight = GetLightsCache().GetSunLight();
    if(pMainLight == nullptr)
    {
        pMainLight = &m_defaultLight;
    }

    return pMainLight;
}

const DepthFramebuffer * CommonRenderer::GetLastZBuffer() const 
{
    return m_zbuffer.get();
}

Vec3 CommonRenderer::NDCToWorld(const Vec2 &ndc) const
{
    assert (GetCamera() != nullptr);
    assert (GetLastZBuffer() != nullptr);
    assert (GetLastZBuffer()->Ready());

    // Read deppth buffer to get depth value for actual pixel
    // We are using the last frame depth buffer as the current one may not have drawn yet
    const int screenX = (ndc.x + 1) * 0.5f * GetRenderSettings().m_resx;
    const int screenY = (ndc.y + 1) * 0.5f * GetRenderSettings().m_resy;
    
    float depth = 0.0f;
    glBindFramebuffer(GL_READ_FRAMEBUFFER, GetLastZBuffer()->FramebufferHandle());
    assert (glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE);
    glReadPixels(screenX, screenY, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &depth);
    glBindFramebuffer(GL_READ_FRAMEBUFFER, 0);

    // Remap from normalised pixel value to normalised depth buffer range
    depth = (2.0f * depth - 1.0f);

    // Deproject
    Mat4 vp = GetCamera()->Projection() * GetCamera()->View();
    Vec4 pos = glm::inverse(vp) * Vec4(ndc.x, ndc.y, depth, 1.0f);

    return Vec3(pos.x, pos.y, pos.z) * (1.0f / pos.w);
}

uint32_t CommonRenderer::ResolutionX() const
{
    return GetRenderSettings().m_resx;
}

uint32_t CommonRenderer::ResolutionY() const
{
    return GetRenderSettings().m_resy;
}

void CommonRenderer::DrawLineGizmo(const Vec3 &from, const Vec3 &to) const
{
    assert (m_line != nullptr);

    Transform identity;
    m_line->UpdateVertex(0, from);
    m_line->UpdateVertex(1, to);
    m_line->Update();

    DrawRenderable(m_line.get(), &identity, DrawMode::Line, nullptr);
}

const LightsCache & CommonRenderer::GetLightsCache() const
{
    return m_lightsCache;
}

void CommonRenderer::PushUniformShaderParams(const ShaderProg *shader, const Transform *tr) const
{
    assert (shader != nullptr);
    assert (tr != nullptr);

    // Update MVP transform matrices
    GLint svViewLoc = glGetUniformLocation(shader->GetHandle(), SV_VIEW);
    GLint svProjLoc = glGetUniformLocation(shader->GetHandle(), SV_PROJECTION);
    GLint svModelLoc = glGetUniformLocation(shader->GetHandle(), SV_MODEL);

    assert (svViewLoc != -1);
    assert (svProjLoc != -1);
    assert (svModelLoc != -1);
    assert (m_activeCam != nullptr);

    glUniformMatrix4fv(svViewLoc, 1, GL_FALSE, &m_activeCam->View()[0][0]);
    glUniformMatrix4fv(svProjLoc, 1, GL_FALSE, &m_activeCam->Projection()[0][0]);
    glUniformMatrix4fv(svModelLoc, 1, GL_FALSE, &tr->Matrix()[0][0]);
}

void CommonRenderer::PushLightShaderParams(const ShaderProg *pShader) const 
{
    // Set main light intensity shader param
    GLint svLightIntensityLoc = glGetUniformLocation(pShader->GetHandle(), SV_MAIN_LIGHT_INTENSITY);
    if(svLightIntensityLoc != -1)
    {
        assert (GetMainLight() != nullptr);
        glUniform1f(svLightIntensityLoc, (GLfloat)GetMainLight()->GetIntensity());
    }

    // Set main light direction shader param
    GLint svLightDirLoc = glGetUniformLocation(pShader->GetHandle(), SV_MAIN_LIGHT_DIR);
    if(svLightDirLoc != -1)
    {
        assert (GetMainLight() != nullptr);

        const GLfloat x = -(GLfloat)GetMainLight()->GetDirection().x;
        const GLfloat y = -(GLfloat)GetMainLight()->GetDirection().y;
        const GLfloat z = -(GLfloat)GetMainLight()->GetDirection().z;
        
        glUniform3f(svLightDirLoc, x, y, z);
    }
}

void CommonRenderer::PushShadowShaderParams(const ShaderProg *pShader) const
{
    GLint svShadowProj0Loc = glGetUniformLocation(pShader->GetHandle(), SV_SHADOW_PROJ0);
    if(svShadowProj0Loc != -1)
    {
        assert (m_shadowRenderer != nullptr);
        glUniformMatrix4fv(svShadowProj0Loc, 1, GL_FALSE, &m_shadowRenderer->GetShadowProjMatrix()[0][0]);
    }

    GLint svShadowBias0Loc = glGetUniformLocation(pShader->GetHandle(), SV_SHADOW_BIAS0);
    if(svShadowBias0Loc != -1)
    {
        assert (m_shadowRenderer != nullptr);
        glUniform1f(svShadowBias0Loc, m_shadowRenderer->GetSettings().m_biasOffset);
    }

    GLint svShadowMap0Loc = glGetUniformLocation(pShader->GetHandle(), SV_SHADOW_MAP0);
    if(svShadowMap0Loc != -1)
    {
        assert (m_shadowRenderer != nullptr);

        glActiveTexture(GL_TEXTURE0 + SHADOW_MAP0_IDX);
        glBindTexture(GL_TEXTURE_2D, m_shadowRenderer->GetShadowMapHandle());
        glUniform1i(svShadowMap0Loc, SHADOW_MAP0_IDX);
        glBindTextureUnit(SHADOW_MAP0_IDX, m_shadowRenderer->GetShadowMapHandle());
    }
}

void CommonRenderer::PushMaterialShaderParams(const ShaderProg &shader, const Material &mat) const
{
    GLint count;
    glGetProgramiv(shader.GetHandle(), GL_ACTIVE_UNIFORMS, &count);
    for(uint32_t i=0; i < count; i++)
    {
        GLchar paramName[256];
        GLenum paramType;
        GLint paramSize;
        GLsizei paramLen;

        glGetActiveUniform(shader.GetHandle(), (GLuint)i, (GLsizei)sizeof(paramName), &paramLen, &paramSize, &paramType, paramName);
        std::string name((char*)&paramName[0], paramLen);
        if(name.size() > 1 &&
            name[0] != 'S' && name[1] != 'V')
        {
            GLint loc = glGetUniformLocation(shader.GetHandle(), name.c_str());
            assert (loc != 1);

            switch(paramType)
            {
                case GL_FLOAT:  { glUniform1f(loc, mat.ShaderParameters()->GetValue<float>(name)); break; }
                case GL_UNSIGNED_INT: { glUniform1ui(loc, mat.ShaderParameters()->GetValue<uint32_t>(name)); break; }
                case GL_INT: { glUniform1i(loc, mat.ShaderParameters()->GetValue<int>(name)); break; }
                case GL_BOOL: { glUniform1i(loc, mat.ShaderParameters()->GetValue<bool>(name)); break; }
                case GL_FLOAT_VEC2: 
                {
                    auto val = mat.ShaderParameters()->GetValue<Vec2>(name);
                    glUniform2f(loc, val.x, val.y); 
                    break; 
                }
                case GL_FLOAT_VEC3: 
                {
                    auto val = mat.ShaderParameters()->GetValue<Vec3>(name);
                    glUniform3f(loc, val.x, val.y, val.z); 
                    break; 
                }
                case GL_FLOAT_VEC4: 
                {
                    auto val = mat.ShaderParameters()->GetValue<Vec4>(name);
                    glUniform4f(loc, val.x, val.y, val.z, val.w); 
                    break; 
                }
                case GL_FLOAT_MAT4: 
                { 
                    glUniformMatrix4fv(loc, 1, GL_FALSE, &mat.ShaderParameters()->GetValue<Mat4>(name)[0][0]);
                    break; 
                }
            }
        }
    }
}

void CommonRenderer::BindMaterialTextures(const ShaderProg &shader, const Material &mat) const
{
    std::vector<std::string> texkeys = mat.ShaderParameters()->TextureKeys();
    for (std::vector<std::string>::iterator it = texkeys.begin() ; it != texkeys.end(); ++it)
    {
        const std::string name = *it;
        const TexVal val = mat.ShaderParameters()->GetTexValue(name);
        if(val.m_tex != nullptr)
        {
            assert (val.m_tex->Ready());
            assert (val.m_tex->GLReady());
            assert (val.m_idx < MAX_USER_TEX_COUNT);

            glActiveTexture(GL_TEXTURE0 + val.m_idx);
            glBindTexture(GL_TEXTURE_2D, val.m_tex->GLHandle());

            GLint loc = glGetUniformLocation(shader.GetHandle(), name.c_str());
            assert (loc != -1);
            glUniform1i(loc, val.m_idx);
            glBindTextureUnit(val.m_idx, val.m_tex->GLHandle());
        }
    }
}

void CommonRenderer::UnbindMaterialTextures(const ShaderProg &shader, const Material &mat) const
{
    std::vector<std::string> texkeys = mat.ShaderParameters()->TextureKeys();
    for (std::vector<std::string>::iterator it = texkeys.begin() ; it != texkeys.end(); ++it)
    {
        const TexVal val = mat.ShaderParameters()->GetTexValue(*it);
        if(val.m_tex != nullptr)
        {
            assert (val.m_tex->Ready());
            assert (val.m_tex->GLReady());
            glBindTexture(GL_TEXTURE_2D, 0);
            glBindTextureUnit(val.m_idx, 0);

        }
    }

    glBindTexture(GL_TEXTURE_2D, 0);
}
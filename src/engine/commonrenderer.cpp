#include "commonrenderer.hpp"
#include "meshgen.hpp"
#include "components/lightcomponent.hpp"

using namespace Engine;

CommonRenderer::CommonRenderer(const RuntimeShaders * const rtShaders):
m_runtimeShaders(rtShaders)
{
    assert (rtShaders != nullptr);
    assert (rtShaders->Ready());

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LINE_SMOOTH);
    glEnable(GL_BLEND);
    glEnable(GL_MULTISAMPLE);
    glDisable(GL_DITHER);

    std::unique_ptr<Mesh> msh = MeshGen::Cube(0.1f);
    m_locator = std::make_unique<Renderable>();
    m_locator->Init(*msh);
    m_locator->BindShader(rtShaders->FlatWhite());

    // Default render settings
    m_settings.m_wireframe = true;

    // Fallback light setup
    m_defaultLight.SetDirection(Vec3(0,1,0));
    m_defaultLight.SetIntensity(1.0f);
}


void CommonRenderer::Clear() const
{
    glClearColor(0, 0, 1, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
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
        default:
            glUseProgram(renderable->GetShader()->GetHandle());
            PushUniformShaderParams(renderable->GetShader(), tr);
            PushLightShaderParams(renderable->GetShader());
            if(mat != nullptr)
            {
                PushMaterialShaderParams(*renderable->GetShader(), *mat);
                BindMaterialTextures(*renderable->GetShader(), *mat);
            }
            break;
    }

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

void CommonRenderer::DrawModel(const Components::ModelComponent *model) const
{
    assert (model != nullptr);
    assert (model->GetModelInstance() != nullptr);
    assert (model->GetModel() != nullptr);
    assert (model->GetModel()->GetRenderable() != nullptr);
    assert (model->GetModel()->GetRenderable()->Ready());

    const Material *mat = model->GetModel()->GetMaterial();
    const Renderable *h = model->GetModel()->GetRenderable();

    // Apply model instance transform
    Transform tr = Transform(model->GetModelInstance()->GetModel()->GetTransform());
    tr.TransformBy(model->GetModelInstance()->GetTransform());    
    
    // Draw call
    DrawRenderable(h, &tr, DrawMode::Fill, mat);
}

void CommonRenderer::DrawModelWire(const Components::ModelComponent *model) const
{
    assert (model != nullptr);
    assert (model->GetModelInstance() != nullptr);
    assert (model->GetModel() != nullptr);
    assert (model->GetModel()->GetRenderable() != nullptr);
    assert (model->GetModel()->GetRenderable()->Ready());

    const Renderable *h = model->GetModel()->GetRenderable();

    // Apply model instance transform
    Transform tr = Transform(model->GetModelInstance()->GetModel()->GetTransform());
    tr.TransformBy(model->GetModelInstance()->GetTransform());   

    // Draw call
    DrawRenderable(h, &tr, DrawMode::Wireframe, nullptr);
}

void CommonRenderer::DrawLocator(const Transform * tr) const
{
    assert (tr != nullptr);
    assert (m_locator != nullptr);

    DrawRenderable(m_locator.get(), tr, DrawMode::Wireframe, nullptr);
}

void CommonRenderer::DrawModelComponents(ECSSys *ecs) const
{
    // Fetch all entities that contain model components
    std::vector<Engine::Entity*> entities;
    ecs->AssetsByComponent<Engine::Components::ModelComponent>(entities);

    // Draw each model component
    for (auto &entity : entities)
    {
        auto cModels = entity->Components().GetAll<Engine::Components::ModelComponent>();
        for(auto &cModel : cModels)
        {
            DrawModel(cModel);

            if(GetRenderSettings().m_wireframe)
            {
                DrawModelWire(cModel);
            }
        }
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
    // Fetch main light
    // If sunlight light has not been set in light cache then use fallback (engine) one
    const DirectionalLight * pMainLight = GetLightsCache().GetSunLight();
    if(pMainLight == nullptr)
    {
        pMainLight = &m_defaultLight;
    }

    // Set main light intensity shader param
    GLint svLightIntensityLoc = glGetUniformLocation(pShader->GetHandle(), SV_MAIN_LIGHT_INTENSITY);
    if(svLightIntensityLoc != -1)
    {
        assert (pMainLight != nullptr);
        glUniform1f(svLightIntensityLoc, (GLfloat)pMainLight->GetIntensity());
    }

    // Set main light direction shader param
    GLint svLightDirLoc = glGetUniformLocation(pShader->GetHandle(), SV_MAIN_LIGHT_DIR);
    if(svLightDirLoc != -1)
    {
        assert (pMainLight != nullptr);

        const GLfloat x = (GLfloat)pMainLight->GetDirection().x;
        const GLfloat y = (GLfloat)pMainLight->GetDirection().y;
        const GLfloat z = (GLfloat)pMainLight->GetDirection().z;
        
        glUniform3f(svLightDirLoc, x, y, z);
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
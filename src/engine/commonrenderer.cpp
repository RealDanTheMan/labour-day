#include "commonrenderer.hpp"

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
            PushUniformShaderParams(renderable->GetShader(), tr);
            break;
        default:
            glUseProgram(renderable->GetShader()->GetHandle());
            PushUniformShaderParams(renderable->GetShader(), tr);
            if(mat != nullptr)
            {
                PushMaterialShaderParams(*renderable->GetShader(), *mat);
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

    glUseProgram(0);
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(2);
    glBindVertexArray(0);
}

void CommonRenderer::DrawModel(const Components::ModelComponent *model) const
{
    assert (model != nullptr);
    assert (model->ModelHandle() != nullptr);
    assert (model->ModelHandle()->GetRenderable().Ready());

    Renderable &h = model->ModelHandle()->GetRenderable();
    Transform *tr = &model->ModelHandle()->GetTransform();
    const Material * const mat = model->ModelHandle()->GetMaterial();
    DrawRenderable(&h, tr, DrawMode::Fill, mat);
}

void CommonRenderer::DrawModelWire(const Components::ModelComponent *model) const
{
    assert (model != nullptr);
    assert (model->ModelHandle() != nullptr);
    assert (model->ModelHandle()->GetRenderable().Ready());

    Renderable &h = model->ModelHandle()->GetRenderable();
    Transform *tr = &model->ModelHandle()->GetTransform();

    DrawRenderable(&h, tr, DrawMode::Wireframe, nullptr);
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

void CommonRenderer::PushUniformShaderParams(const ShaderProg *shader, const Transform *tr) const
{
    assert (shader != nullptr);
    assert (tr != nullptr);

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
                case GL_SAMPLER_2D: 
                {
                     break; 
                }
            }
        }
    }
}
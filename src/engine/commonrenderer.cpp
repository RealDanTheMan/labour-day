#include "commonrenderer.hpp"

using namespace Engine;

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
        DrawRenderable(m_queue[i], nullptr);
    }
}

void CommonRenderer::DrawRenderable(const Renderable *renderable, const Transform *tr) const
{
    assert (renderable != nullptr);
    assert (renderable->Ready());

    glUseProgram(renderable->GetShader()->GetHandle());
    PushUniformShaderParams(renderable->GetShader(), tr);

    glBindVertexArray(renderable->VertexAttributes());
    glDrawElements(GL_TRIANGLES, renderable->IndexCount(), GL_UNSIGNED_INT, 0);

    glUseProgram(0);
    glBindVertexArray(0);
}

void CommonRenderer::DrawModel(const Components::ModelComponent *model) const
{
    assert (model != nullptr);
    assert (model->ModelHandle() != nullptr);
    assert (model->ModelHandle()->GetRenderable().Ready());

    Renderable &h = model->ModelHandle()->GetRenderable();
    Transform *tr = &model->ModelHandle()->GetTransform();
    DrawRenderable(&h, tr);
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
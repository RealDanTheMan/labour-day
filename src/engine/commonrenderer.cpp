#include "commonrenderer.hpp"

using namespace Engine;

void CommonRenderer::Clear() const
{
    glClearColor(0, 0, 1, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void CommonRenderer::DrawRenderables() const
{
    for (uint32_t i=0; i < m_queue.size(); i++)
    {
        DrawRenderable(m_queue[i]);
    }
}

void CommonRenderer::DrawRenderable(const Renderable *renderable) const
{
    glUseProgram(renderable->GetShader()->GetHandle());
    glBindVertexArray(renderable->VertexAttributes());
    glDrawElements(GL_TRIANGLES, renderable->VertexCount(), GL_UNSIGNED_INT, 0);

    glUseProgram(0);
    glBindVertexArray(0);
}

void CommonRenderer::ClearQueue()
{
    m_queue.clear();
}

void CommonRenderer::AddToQueue(const Renderable *renderable)
{
    m_queue.push_back(renderable);
}
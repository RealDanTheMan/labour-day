#include "renderable.hpp"

using namespace Engine;

Renderable::Renderable():
m_vertices(nullptr),
m_indices(nullptr),
m_shader(nullptr),
m_vertexCount(0),
m_indexCount(0)
{

}

void Renderable::Init(glm::vec3 *vertices, uint32_t *indices, const uint32_t vCount, const uint32_t iCount)
{
    m_vertices = std::make_unique<glm::vec3[]>(vCount);
    m_indices = std::make_unique<uint32_t[]>(iCount);
    m_vertexCount = vCount;
    m_indexCount = iCount;

    for(uint32_t i=0; i < vCount; i++)
    {
        m_vertices[i] = vertices[i];
    }

    for(uint32_t i=0; i < iCount; i++)
    {
        m_indices[i] = indices[i];
    }
}

void Renderable::Free()
{
    glDeleteBuffers(1, &m_vbo);
    glDeleteBuffers(1, &m_ibo);
    
    m_vertices.reset(nullptr);
    m_indices.reset(nullptr);
    m_vertices = nullptr;
    m_indices = nullptr;
    m_shader = nullptr;
    m_vertexCount = 0;
    m_indexCount = 0;
}

void Renderable::BindShader(ShaderProg* shader)
{
    m_shader = shader;
}

const uint32_t Renderable::VertexCount() const
{
    return m_vertexCount;
}

const uint32_t Renderable::IndexCount() const
{
    return m_indexCount;
}

const ShaderProg* Renderable::GetShader() const
{
    return m_shader;
}

void Renderable::InitBuffers()
{
    assert (m_vbo == 0);
    assert (m_ibo == 0);

    glGenBuffers(1, &m_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, m_vertexCount * sizeof(glm::vec3), m_vertices.get(), GL_STATIC_DRAW);
    
    glGenBuffers(1, &m_ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indexCount * sizeof(uint32_t), m_indices.get(), GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
#include "dynamicrenderable.hpp"

using namespace Engine;

void DynamicRenderable::UpdateVertex(const uint32_t idx, const Vec3 &vertex)
{
    assert (idx < VertexCount());
    m_vertices[idx] = vertex;
}

void DynamicRenderable::UpdateNormal(const uint32_t idx, const Vec3 &normal)
{
    assert (idx < VertexCount());
    m_normals[idx] = normal;
}

void DynamicRenderable::UpdateTexcoord0(const uint32_t idx, const Vec2 &texcoord)
{
    assert (idx < VertexCount());
    m_texcoords0[idx] = texcoord;
}

void DynamicRenderable::Update()
{
    assert (Ready());

    glBindVertexArray(m_vao);

    // Update vertex data
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, VertexCount() * sizeof(Vec3), m_vertices.get(), GL_DYNAMIC_DRAW);

    // Update normal data
    glBindBuffer(GL_ARRAY_BUFFER, m_nbo);
    glBufferData(GL_ARRAY_BUFFER, VertexCount() * sizeof(Vec3), m_normals.get(), GL_DYNAMIC_DRAW);

    // Update texcoord 0 data
    glBindBuffer(GL_ARRAY_BUFFER, m_t0bo);
    glBufferData(GL_ARRAY_BUFFER, VertexCount() * sizeof(Vec2), m_texcoords0.get(), GL_DYNAMIC_DRAW);

    // Unbind buffer access to keep states clear
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
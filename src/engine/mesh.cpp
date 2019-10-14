#include "mesh.hpp"

using namespace Engine;

Mesh::Mesh():
m_vertices(nullptr),
m_indices(nullptr),
m_vCount(0),
m_iCount(0)
{

}

void Mesh::SetMeshData(const glm::vec3 *vertices, const unsigned int* indices, const uint32_t vCount, const uint32_t iCount)
{
    m_vertices = std::make_unique<glm::vec3[]>(vCount);
    m_indices = std::make_unique<unsigned int[]>(iCount);
    m_vCount = vCount;
    m_iCount = iCount;

    for(uint32_t i=0; i < vCount; i++)
    {
        m_vertices[i] = vertices[i];
    }

    for(uint32_t i=0; i < iCount; i++)
    {
        m_indices[i] = indices[i];
    }
}

void Mesh::Free()
{
    m_vertices.reset();
    m_indices.reset();
    m_vertices = nullptr;
    m_indices = nullptr;

    m_vCount = 0;
    m_iCount = 0;
}

const uint32_t Mesh::VertexCount() const
{
    return m_vCount;
}

const uint32_t Mesh::IndexCount() const
{
    return m_iCount;
}

glm::vec3* Mesh::Vertices() 
{
    assert (m_vertices != nullptr);
    return m_vertices.get();
}

unsigned int* Mesh::Indices()
{
    assert (m_indices != nullptr);
    return m_indices.get();
}
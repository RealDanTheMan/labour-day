#include "mesh.hpp"
#include <vector>

using namespace Engine;

Mesh::Mesh():
m_vertices(nullptr),
m_normals(nullptr),
m_indices(nullptr),
m_vCount(0),
m_nCount(0),
m_iCount(0)
{

}

void Mesh::SetMeshData(const Vec3 *vertices, const unsigned int* indices, const uint32_t vCount, const uint32_t iCount)
{
    assert (vertices != nullptr);
    assert (indices != nullptr);
    
    m_vertices = std::make_unique<Vec3[]>(vCount);
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

void Mesh::SetNormals(const Vec3* normals, const uint32_t count)
{
    assert (normals != nullptr);
    assert (count == VertexCount());

    m_normals = std::make_unique<Vec3[]>(count);
    m_nCount = count;
    
    for(uint32_t i=0; i < count; i++)
    {
        m_normals[i] = normals[i];
    }
}

void Mesh::Free()
{
    m_vertices.reset();
    m_normals.reset();
    m_indices.reset();
    m_vertices = nullptr;
    m_normals = nullptr;
    m_indices = nullptr;

    m_vCount = 0;
    m_nCount = 0;
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

const uint32_t Mesh::NormalCount() const
{
    return m_nCount;
}

Vec3* Mesh::Vertices() 
{
    assert (m_vertices != nullptr);
    return m_vertices.get();
}

Vec3* Mesh::Normals() 
{
    assert (m_normals != nullptr);
    return m_normals.get();
}

unsigned int* Mesh::Indices()
{
    assert (m_indices != nullptr);
    return m_indices.get();
}

const Vec3 &Mesh::Vertex(const uint32_t idx) const
{
    assert (m_vertices != nullptr);
    assert (idx < m_vCount);

    return m_vertices[idx];
}

const Vec3 &Mesh::Normal(const uint32_t idx) const
{
    assert (m_normals != nullptr);
    assert (idx < m_nCount);

    return m_normals[idx];
}

const uint32_t &Mesh::VertexIndex(const uint32_t idx) const
{
    assert (m_indices != nullptr);
    assert (idx < m_iCount);

    return m_indices[idx];
}
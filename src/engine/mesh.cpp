#include "mesh.hpp"
#include <vector>

using namespace Engine;

Mesh::Mesh():
m_vertices(nullptr),
m_normals(nullptr),
m_texcoords0(nullptr),
m_indices(nullptr),
m_vCount(0),
m_nCount(0),
m_t0Count(0),
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

void Mesh::SetTexcoords(const Vec2* texcoords, const uint32_t count, const uint32_t id)
{
    assert (texcoords != nullptr);
    assert (count == VertexCount());
    
    // TODO: For now we only allow for 1 uv channel
    assert (id == 0);

    m_texcoords0 = std::make_unique<Vec2[]>(count);
    m_t0Count = count;
    
    for(uint32_t i=0; i < count; i++)
    {
        m_texcoords0[i] = texcoords[i];
    }
}

void Mesh::Free()
{
    m_vertices.reset();
    m_normals.reset();
    m_texcoords0.reset();
    m_indices.reset();
    m_vertices = nullptr;
    m_normals = nullptr;
    m_texcoords0 = nullptr;
    m_indices = nullptr;

    m_vCount = 0;
    m_nCount = 0;
    m_t0Count = 0;
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

const uint32_t Mesh::TexcoordCount(const uint32_t id) const
{
    // TODO: For now we only support 1 uv channel
    assert (id == 0);
    return m_t0Count;
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

Vec2* Mesh::Texcoords(const uint32_t id)
{
    // TODO: For now we only support 1 uv channel
    assert (id == 0);
    assert (m_texcoords0 != nullptr);

    return m_texcoords0.get();
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

const Vec2 &Mesh::Texcoord(const uint32_t idx, const uint32_t id) const
{
    // TODO: For now we only support 1 uv channel
    assert(id == 0);
    assert (m_texcoords0 != nullptr);
    assert (idx < m_t0Count);

    return m_texcoords0[idx];
}

const uint32_t &Mesh::VertexIndex(const uint32_t idx) const
{
    assert (m_indices != nullptr);
    assert (idx < m_iCount);

    return m_indices[idx];
}
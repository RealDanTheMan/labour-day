#ifndef MESH_HPP_
#define MESH_HPP_

#include "types.hpp"
#include "iresource.hpp"
#include <memory>
#include <glm/vec3.hpp>

namespace Engine
{
    class Mesh : public IResource
    {
        public:

        Mesh();
        Mesh(const Mesh &rhs) = delete;
        Mesh &operator=(const Mesh &rhs) = delete;

        void SetMeshData(const Vec3* verts, const unsigned int* indices, const uint32_t vCount, const uint32_t iCount);
        void SetNormals(const Vec3* normals, const uint32_t count);
        void SetTexcoords(const Vec2* texcoords, const uint32_t count, const uint32_t id);
        void Unload() override;
        Vec3* Vertices() ;
        Vec3* Normals() ;
        Vec2* Texcoords(const uint32_t id) ;
        unsigned int* Indices() ;
        const uint32_t VertexCount() const;
        const uint32_t NormalCount() const;
        const uint32_t TexcoordCount(const uint32_t id) const;
        const uint32_t IndexCount() const;

        const Vec3 &Vertex(const uint32_t idx) const;
        const Vec3 &Normal(const uint32_t idx) const;
        const Vec2 &Texcoord(const uint32_t idx, const uint32_t id) const;
        const uint32_t &VertexIndex(const uint32_t idx) const;

        private:

        std::unique_ptr<Vec3[]> m_vertices;
        std::unique_ptr<Vec3[]> m_normals;
        std::unique_ptr<Vec2[]> m_texcoords0;
        std::unique_ptr<unsigned int[]> m_indices;
        uint32_t m_vCount;
        uint32_t m_nCount;
        uint32_t m_t0Count;
        uint32_t m_iCount;
    };
}

#endif
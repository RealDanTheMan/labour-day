#ifndef MESH_H_
#define MESH_H_

#include <memory>
#include <glm/vec3.hpp>

namespace Engine
{
    class Mesh
    {
        public:

        Mesh();
        Mesh(const Mesh &rhs) = delete;
        Mesh &operator=(const Mesh &rhs) = delete;

        void SetMeshData(const glm::vec3* verts, const unsigned int* indices, const uint32_t vCount, const uint32_t iCount);
        void Free();
        glm::vec3* Vertices() ;
        unsigned int* Indices() ;
        const uint32_t VertexCount() const;
        const uint32_t IndexCount() const;

        private:

        std::unique_ptr<glm::vec3[]> m_vertices;
        std::unique_ptr<unsigned int[]> m_indices;
        uint32_t m_vCount;
        uint32_t m_iCount;
    };
}

#endif
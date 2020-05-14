#ifndef RENDERABLE_HPP_
#define RENDERABLE_HPP_

#include "mesh.hpp"
#include "shaderprog.hpp"
#include <glm/vec3.hpp>
#include <memory>

namespace Engine
{
    class Renderable
    {
        public:

        Renderable();
        void Init(glm::vec3 *vertices, uint32_t *indices, const uint32_t vCount, const uint32_t iCount);
        void Init(const Mesh &mesh);
        void Free();
        void BindShader(const ShaderProg* shader);
        const ShaderProg* GetShader() const;
        const uint32_t VertexCount() const;
        const uint32_t NormalCount() const;
        const uint32_t IndexCount() const;

        const GLuint IndexBuffer() const;
        const GLuint VertexBuffer() const;
        const GLuint NormalBuffer() const;
        const GLuint VertexAttributes() const;
        const bool Ready() const;

        private:

        void InitBuffers();
        void BuffersGood();

        std::unique_ptr<glm::vec3[]> m_vertices;
        std::unique_ptr<glm::vec3[]> m_normals;
        std::unique_ptr<unsigned int[]> m_indices;
        const ShaderProg* m_shader;
        uint32_t m_vertexCount;
        uint32_t m_normalCount;
        uint32_t m_indexCount;

        GLuint m_vbo;
        GLuint m_nbo;
        GLuint m_ibo;
        GLuint m_vao;
    };
}

#endif
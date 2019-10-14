#include "meshgen.hpp"

using namespace Engine;

std::unique_ptr<Mesh> MeshGen::Triangle(const float scale)
{
    const float halfScale = scale * 0.5;
    const glm::vec3 vertices[3] = {glm::vec3(0.0f, halfScale, 0.0f), glm::vec3(halfScale, -halfScale, 0.0f), glm::vec3(-halfScale, -halfScale, 0.0f)};
    const unsigned int indices[3] = {0, 1, 2};

    std::unique_ptr<Mesh> mesh = std::make_unique<Mesh>();
    mesh->SetMeshData(vertices, indices, 3, 3);

    return mesh;
}
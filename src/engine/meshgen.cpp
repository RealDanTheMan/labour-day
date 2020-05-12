#include "meshgen.hpp"
#include "types.hpp"

using namespace Engine;

std::unique_ptr<Mesh> MeshGen::Triangle(const float scale)
{
    const float halfScale = scale * 0.5;
    const glm::vec3 vertices[3] =
    {
        Vec3(0.0f, halfScale, 0.0f), 
        Vec3(halfScale, -halfScale, 0.0f), 
        Vec3(-halfScale, -halfScale, 0.0f)
    }
    ;
    const unsigned int indices[3] = 
    {
        0, 1, 2
    };

    std::unique_ptr<Mesh> mesh = std::make_unique<Mesh>();
    mesh->SetMeshData(vertices, indices, 3, 3);

    return mesh;
}


std::unique_ptr<Mesh> MeshGen::Cube(const float scale)
{
    const float halfScale = scale * 0.5;
    const glm::vec3 vertices[8] = 
    {
        Vec3(-halfScale, -halfScale, halfScale),
        Vec3(halfScale, -halfScale, halfScale),
        Vec3(-halfScale, halfScale, halfScale),
        Vec3(halfScale, halfScale, halfScale),
        Vec3(-halfScale, halfScale, -halfScale),
        Vec3(halfScale, halfScale, -halfScale),
        Vec3(-halfScale, -halfScale, -halfScale),
        Vec3(halfScale, -halfScale, -halfScale)
    };
    
    const unsigned int indices[36] = 
    {
        0, 1, 2,
        2, 1, 3,
        
        2, 3, 4,
        4, 3, 5,
        
        4, 5, 6,
        6, 5, 7,
        
        6, 7, 0,
        0, 7, 1,
        
        1, 7, 3,
        3, 7, 5,
        
        6, 0, 4,
        4, 0, 2
    };

    std::unique_ptr<Mesh> mesh = std::make_unique<Mesh>();
    mesh->SetMeshData(vertices, indices, 8, 36);

    return mesh;
}
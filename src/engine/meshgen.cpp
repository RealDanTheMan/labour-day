#include "meshgen.hpp"
#include "types.hpp"

#include "../external/OBJ_Loader.hpp"

using namespace Engine;

std::unique_ptr<Mesh> MeshGen::Triangle(const float scale)
{
    const float halfScale = scale * 0.5;
    const Vec3 vertices[3] =
    {
        Vec3(0.0f, halfScale, 0.0f), 
        Vec3(halfScale, -halfScale, 0.0f), 
        Vec3(-halfScale, -halfScale, 0.0f)
    };

    const Vec3 normals[3] =
    {
        Vec3(0.0f, 1.0f, 0.0f), 
        Vec3(0.0f, 1.0f, 0.0f), 
        Vec3(0.0f, 1.0f, 0.0f)
    };

    const unsigned int indices[3] = 
    {
        0, 1, 2
    };

    std::unique_ptr<Mesh> mesh = std::make_unique<Mesh>();
    mesh->SetMeshData(vertices, indices, 3, 3);
    mesh->SetNormals(normals, 3);

    return mesh;
}


std::unique_ptr<Mesh> MeshGen::Cube(const float scale)
{
    const float halfScale = scale * 0.5;
    const Vec3 vertices[8] = 
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

    const Vec3 normals[8] =
    {
        Vec3(0.0f, 1.0f, 0.0f),
        Vec3(0.0f, 1.0f, 0.0f),
        Vec3(0.0f, 1.0f, 0.0f),
        Vec3(0.0f, 1.0f, 0.0f),
        Vec3(0.0f, 1.0f, 0.0f),
        Vec3(0.0f, 1.0f, 0.0f),
        Vec3(0.0f, 1.0f, 0.0f),
        Vec3(0.0f, 1.0f, 0.0f)
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
    mesh->SetNormals(normals, 8);

    return mesh;
}

std::unique_ptr<Mesh> MeshGen::Box(const float width, const float height, const float depth)
{
    const float hWidth = width * 0.5;
    const float hHeight = height * 0.5;
    const float hDepth = depth * 0.5;

    const Vec3 vertices[24] = 
    {
        // Front plane
        Vec3(-hWidth, -hHeight, hDepth),
        Vec3(hWidth, -hHeight, hDepth),
        Vec3(-hWidth, hHeight, hDepth),
        Vec3(hWidth, hHeight, hDepth),

        // Back plane
        Vec3(-hWidth, -hHeight, -hDepth),
        Vec3(hWidth, -hHeight, -hDepth),
        Vec3(-hWidth, hHeight, -hDepth),
        Vec3(hWidth, hHeight, -hDepth),

        // Top plane
        Vec3(-hWidth, hHeight, -hDepth),
        Vec3(hWidth, hHeight, -hDepth),
        Vec3(-hWidth, hHeight, hDepth),
        Vec3(hWidth, hHeight, hDepth),

        // Bottom plane
        Vec3(-hWidth, -hHeight, -hDepth),
        Vec3(hWidth, -hHeight, -hDepth),
        Vec3(-hWidth, -hHeight, hDepth),
        Vec3(hWidth, -hHeight, hDepth),

        // Left plane
        Vec3(-hWidth, hHeight, -hDepth),
        Vec3(-hWidth, hHeight, hDepth),
        Vec3(-hWidth, -hHeight, -hDepth),
        Vec3(-hWidth, -hHeight, hDepth),

        // Right plane
        Vec3(hWidth, hHeight, -hDepth),
        Vec3(hWidth, hHeight, hDepth),
        Vec3(hWidth, -hHeight, -hDepth),
        Vec3(hWidth, -hHeight, hDepth),
    };

    const Vec3 normals[24] =
    {
        // Front plane
        Vec3(0.0f, 0.0f, 1.0f),
        Vec3(0.0f, 0.0f, 1.0f),
        Vec3(0.0f, 0.0f, 1.0f),
        Vec3(0.0f, 0.0f, 1.0f),

        // Back plane
        Vec3(0.0f, 0.0f, -1.0f),
        Vec3(0.0f, 0.0f, -1.0f),
        Vec3(0.0f, 0.0f, -1.0f),
        Vec3(0.0f, 0.0f, -1.0f),

        // Top plane
        Vec3(0.0f, 1.0f, 0.0f),
        Vec3(0.0f, 1.0f, 0.0f),
        Vec3(0.0f, 1.0f, 0.0f),
        Vec3(0.0f, 1.0f, 0.0f),

        // Bottom plane
        Vec3(0.0f, -1.0f, 0.0f),
        Vec3(0.0f, -1.0f, 0.0f),
        Vec3(0.0f, -1.0f, 0.0f),
        Vec3(0.0f, -1.0f, 0.0f),

        // Left plane
        Vec3(-1.0f, 0.0f, 0.0f),
        Vec3(-1.0f, 0.0f, 0.0f),
        Vec3(-1.0f, 0.0f, 0.0f),
        Vec3(-1.0f, 0.0f, 0.0f),

        // Right plane
        Vec3(1.0f, 0.0f, 0.0f),
        Vec3(1.0f, 0.0f, 0.0f),
        Vec3(1.0f, 0.0f, 0.0f),
        Vec3(1.0f, 0.0f, 0.0f)

    };

    const Vec2 texcoords[24] =
    {
        Vec2(0.0, 0.0), Vec2(1.0, 0.0), Vec2(0.0, 1.0), Vec2(1.0, 1.0),
        Vec2(0.0, 0.0), Vec2(1.0, 0.0), Vec2(0.0, 1.0), Vec2(1.0, 1.0),
        Vec2(0.0, 0.0), Vec2(1.0, 0.0), Vec2(0.0, 1.0), Vec2(1.0, 1.0),
        Vec2(0.0, 0.0), Vec2(1.0, 0.0), Vec2(0.0, 1.0), Vec2(1.0, 1.0),
        Vec2(0.0, 0.0), Vec2(1.0, 0.0), Vec2(0.0, 1.0), Vec2(1.0, 1.0),
        Vec2(0.0, 0.0), Vec2(1.0, 0.0), Vec2(0.0, 1.0), Vec2(1.0, 1.0)
    };
    
    const unsigned int indices[36] = 
    {
        // Front plane
        0, 2, 3,
        0, 3, 1,

        // Back plane
        4, 6, 7,
        4, 7, 5,

        // Top plane
        10, 8, 9,
        10, 9, 11,

        // Bottom plane
        14, 12, 13,
        14, 13, 15,

        // Left plane
        18, 16, 17,
        18, 17, 19,

        // Right plane
        22, 20, 21,
        22, 21, 23,
    };

    std::unique_ptr<Mesh> mesh = std::make_unique<Mesh>();
    mesh->SetMeshData(vertices, indices, 24, 36);
    mesh->SetNormals(normals, 24);
    mesh->SetTexcoords(texcoords, 24, 0);

    return mesh;
}

std::unique_ptr<Mesh> MeshGen::FromOBJ(const std::string &filepath)
{
    auto parser = objl::Loader();
    bool status = parser.LoadFile(filepath);
    if(status)
    {
        std::vector<Vec3> vertices;
        std::vector<Vec3> normals;
        std::vector<Vec2> texcoords;
        std::vector<unsigned int> indices;

        for (std::vector<objl::Vertex>::iterator it = parser.LoadedVertices.begin() ; it != parser.LoadedVertices.end(); ++it)
        {
            objl::Vertex data = *it;
            vertices.push_back(Vec3(data.Position.X, data.Position.Y, data.Position.Z));
            normals.push_back(Vec3(data.Normal.X, data.Normal.Y, data.Normal.Z));
            texcoords.push_back(Vec2(data.TextureCoordinate.X, data.TextureCoordinate.Y));
        }

        for (std::vector<unsigned int>::iterator it = parser.LoadedIndices.begin() ; it != parser.LoadedIndices.end(); ++it)
        {
            indices.push_back(*it);
        }

        auto msh = std::make_unique<Mesh>();
        msh->SetMeshData(&vertices[0], &indices[0], vertices.size(), indices.size());
        msh->SetNormals(&normals[0], normals.size());
        msh->SetTexcoords(&texcoords[0], texcoords.size(), 0);

        return msh;
    }

    return nullptr;
}
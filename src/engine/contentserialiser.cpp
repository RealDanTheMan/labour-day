#include "contentserialiser.hpp"
#include "../external/OBJ_Loader.hpp"

using namespace Engine;

std::unique_ptr<ContentMaterialInfo> ContentMaterialInfo::FromJSON(const configuru::Config &json)
{
    if(json.has_key("type") && json["type"] == "Material")
    {
        std::unique_ptr<ContentMaterialInfo> info = std::make_unique<ContentMaterialInfo>();
        info->m_name = json["name"].as_string();
        info->m_shaderKey = json["shader"].as_string();

        return info;
    }

    return nullptr;
}

std::unique_ptr<ContentModelInfo> ContentModelInfo::FromJSON(const configuru::Config &json)
{
    if(json.has_key("type") && json["type"] == "Model")
    {
        std::unique_ptr<ContentModelInfo> info = std::make_unique<ContentModelInfo>();
        info->m_name = json["name"].as_string();
        info->m_materialKey = json["material"].as_string();
        info->m_meshKey = json["mesh"].as_string();

        return info;
    }

    return nullptr;
}


std::unique_ptr<Mesh> ContentSerialiser::LoadMesh(const std::string &filepath)
{
    if(SysUtils::FileExists(filepath))
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
    }

    return nullptr;
}

std::unique_ptr<ContentModelInfo> ContentSerialiser::LoadModelInfo(const std::string &filepath)
{
    if(SysUtils::FileExists(filepath))
    {
        bool good = false;
        configuru::Config cfg;

        try
        {
            cfg = configuru::parse_file(filepath, configuru::JSON);
            good = true;
        }
        catch(configuru::ParseError  &err)
        {
            D_ERR("Failed to parse json model file !");
            D_ERR(err.what());
        }

        if(good)
        {
            auto info = ContentModelInfo::FromJSON(cfg);
            return info;
        }
    }

    return nullptr;
}

std::unique_ptr<ContentMaterialInfo> ContentSerialiser::LoadMaterialInfo(const std::string &filepath)
{
    if(SysUtils::FileExists(filepath))
    {
        bool good = false;
        configuru::Config cfg;

        try
        {
            cfg = configuru::parse_file(filepath, configuru::JSON);
            good = true;
        }
        catch(configuru::ParseError  &err)
        {
            D_ERR("Failed to parse json material file !");
            D_ERR(err.what());
        }

        if(good)
        {
            auto info = ContentMaterialInfo::FromJSON(cfg);
            return info;
        }
    }
    
    return nullptr;
}

std::unique_ptr<Prefab> ContentSerialiser::LoadPrefab(const std::string &filepath)
{
    if(SysUtils::FileExists(filepath))
    {
        bool good = false;
        configuru::Config cfg;

        try
        {
            cfg = configuru::parse_file(filepath, configuru::JSON);
            good = true;
        }
        catch(configuru::ParseError  &err)
        {
            D_ERR("Failed to parse json prefab file !");
            D_ERR(err.what());
        }
        
        if(good)
        {
            auto ent = EntitySerialiser::Deserialise (cfg);
            if(ent != nullptr)
            {
                auto prf = std::make_unique<Prefab>(*ent);
                return prf;
            }
        }
    }

    return nullptr;
}
#include "contentserialisation.hpp"
#include "debugging.hpp"
#include <iostream>
#include <sstream>

using namespace Engine;

std::unique_ptr<ContentMaterialInfo> ContentMaterialInfo::FromJSON(const configuru::Config &json)
{
    if(json.has_key("type") && json["type"] == "Material")
    {
        auto info = std::make_unique<ContentMaterialInfo>();
        info->m_name = json["name"].as_string();
        info->m_shaderKey = json["shader"].as_string();

        if(json.has_key("parameters") && json["parameters"].is_array())
        {
            for(const configuru::Config &elem : json["parameters"].as_array())
            {
                assert (elem.has_key("name"));
                assert (elem.has_key("value"));
                assert (elem.has_key("type"));

                auto param = std::make_unique<ContentPropertyInfo>();
                param->m_name = elem["name"].as_string();
                param->m_value = elem["value"].as_string();
                param->m_type = elem["type"].as_string();

                info->m_params.push_back(std::move(param));
            }
        }

        return info;
    }

    return nullptr;
}

std::unique_ptr<ContentModelInfo> ContentModelInfo::FromJSON(const configuru::Config &json)
{
    if(json.has_key("type") && json["type"] == "Model")
    {
        auto info = std::make_unique<ContentModelInfo>();
        info->m_name = json["name"].as_string();
        info->m_materialKey = json["material"].as_string();
        info->m_meshKey = json["mesh"].as_string();

        return info;
    }

    return nullptr;
}

std::unique_ptr<ContentEntityInfo> ContentEntityInfo::FromJSON(const configuru::Config &json)
{
    if(json.has_key("type") && json["type"] == "Entity")
    {
        auto info = std::make_unique<ContentEntityInfo>();
        info->m_name = json["name"].as_string();

        // Read all component data
        if(json.has_key("components") && json["components"].is_array())
        {
            for (const configuru::Config& element : json["components"].as_array()) 
            {
                std::unique_ptr<ContentEntityComponentInfo> cInfo = ContentEntityComponentInfo::FromJSON(element);
                assert (cInfo != nullptr);

                if(cInfo != nullptr)
                {
                    info->m_components.push_back(std::move(cInfo));
                }
            }
        }

        // Read all children entities (recursive)
        if(json.has_key("children") && json["children"].is_array())
        {
            for (const configuru::Config& element : json["children"].as_array()) 
            {
                std::unique_ptr<ContentEntityInfo> cInfo = ContentEntityInfo::FromJSON(element);
                assert (cInfo != nullptr);

                if(cInfo != nullptr)
                {
                    info->m_children.push_back(std::move(cInfo));
                }
            }
        }

        // Read entity tags
        if(json.has_key("tags") && json["tags"].is_array())
        {
            for(const configuru::Config &elem : json["tags"].as_array())
            {
                if(elem.has_key("value"))
                {
                    info->m_tags.push_back(elem["value"].as_string());
                }
            }
        }

        return info;
    }

    return nullptr;
}

std::unique_ptr<ContentEntityComponentInfo> ContentEntityComponentInfo::FromJSON(const configuru::Config &json)
{
    if(json.has_key("type"))
    {
        assert (json.has_key("name"));
        auto info = std::make_unique<ContentEntityComponentInfo>();
        info->m_type = json["type"].as_string();
        info->m_name = json["name"].as_string();

        if(json.has_key("properties") && json["properties"].is_array())
        {
            for (const configuru::Config& property : json["properties"].as_array()) 
            {
                std::unique_ptr<ContentPropertyInfo> pInfo = ContentPropertyInfo::FromJSON(property);
                assert(pInfo != nullptr);

                if(pInfo != nullptr)
                {
                    info->m_properties.push_back(std::move(pInfo));
                }
            }
        }

        return info;
    }

    return nullptr;
}

std::unique_ptr<ContentManifestInfo> ContentManifestInfo::FromJSON(const configuru::Config & json)
{
    if(json.has_key("type") && json["type"] == "AssetManifest")
    {
        auto info = std::make_unique<ContentManifestInfo>();

        // Load texture asset entries
        if(json.has_key("textures") && json["textures"].is_array())
        {
            for (const configuru::Config& element : json["textures"].as_array()) 
            {
                assert (element.has_key("path") && element["path"].as_string().size() > 0);
                assert (element.has_key("key") && element["key"].as_string().size() > 0);

                info->m_textures.insert(std::make_pair(
                    element["key"].as_string(),
                    element["path"].as_string()
                ));
            }
        }

        // Load mesh asset entries
        if(json.has_key("meshes") && json["meshes"].is_array())
        {
            for (const configuru::Config& element : json["meshes"].as_array()) 
            {
                assert (element.has_key("path") && element["path"].as_string().size() > 0);
                assert (element.has_key("key") && element["key"].as_string().size() > 0);

                info->m_meshes.insert(std::make_pair(
                    element["key"].as_string(),
                    element["path"].as_string()
                ));
            }
        }

        // Load material asset entries
        if(json.has_key("materials") && json["materials"].is_array())
        {
            for (const configuru::Config& element : json["materials"].as_array()) 
            {
                assert (element.has_key("path") && element["path"].as_string().size() > 0);
                assert (element.has_key("key") && element["key"].as_string().size() > 0);

                info->m_materials.insert(std::make_pair(
                    element["key"].as_string(),
                    element["path"].as_string()
                ));
            }
        }


        // Load model asset entries
        if(json.has_key("models") && json["models"].is_array())
        {
            for (const configuru::Config& element : json["models"].as_array()) 
            {
                assert (element.has_key("path") && element["path"].as_string().size() > 0);
                assert (element.has_key("key") && element["key"].as_string().size() > 0);

                info->m_models.insert(std::make_pair(
                    element["key"].as_string(),
                    element["path"].as_string()
                ));
            }
        }

        // Load prefab asset entries
        if(json.has_key("prefabs") && json["prefabs"].is_array())
        {
            for (const configuru::Config& element : json["prefabs"].as_array()) 
            {
                assert (element.has_key("path") && element["path"].as_string().size() > 0);
                assert (element.has_key("key") && element["key"].as_string().size() > 0);

                info->m_prefabs.insert(std::make_pair(
                    element["key"].as_string(),
                    element["path"].as_string()
                ));
            }
        }

        return info;
    }

    return nullptr;
}

void ContentManifestInfo::Printout() const
{
    std::cout << "--- Asset Manifest ---" << std::endl << std::endl;
    
    for(auto it = m_textures.begin(); it !=  m_textures.end(); ++it) 
    {
        std::cout << "Texture Asset: " << it->second << " :: " << it->first << std::endl;
    }

    for(auto it = m_meshes.begin(); it !=  m_meshes.end(); ++it) 
    {
        std::cout << "Mesh Asset: " << it->second << " :: " << it->first << std::endl;
    }

    for(auto it = m_materials.begin(); it !=  m_materials.end(); ++it) 
    {
        std::cout << "Material Asset: " << it->second << " :: " << it->first << std::endl;
    }

    for(auto it = m_models.begin(); it !=  m_models.end(); ++it) 
    {
        std::cout << "Model Asset: " << it->second << " :: " << it->first << std::endl;
    }

    for(auto it = m_prefabs.begin(); it !=  m_prefabs.end(); ++it) 
    {
        std::cout << "Prefab Asset: " << it->second << " :: " << it->first << std::endl;
    }

    std::cout << "--- -------------- ---" << std::endl << std::endl;
}

std::unique_ptr<ContentLevelObjectInfo> ContentLevelObjectInfo::FromJSON(const configuru::Config & json)
{
    if(json.has_key("type") && json["type"] == "LevelObject")
    {
        auto info = std::make_unique<ContentLevelObjectInfo>();
        
        if(json.has_key("id") && json["id"].as_string().size() > 0)
        {
            info->m_id = json["id"].as_string();
        }

        if(json.has_key("position") && json["position"].as_string().size() > 0)
        {
            info->m_pos = json["position"].as_string();
        }

        return info;
    }

    return nullptr;
}

std::string ContentLevelObjectInfo::ToString() const
{
    std::stringstream ss;
    ss << "LevelObject of " << m_id << " at [" << m_pos << "]";

    return ss.str();
}

std::unique_ptr<ContentLevelInfo> ContentLevelInfo::FromJSON(const configuru::Config & json)
{
    if(json.has_key("type") && json["type"] == "Level")
    {
        auto info = std::make_unique<ContentLevelInfo>();
        
        if(json.has_key("name") && json["name"].as_string().size() > 0)
        {
            info->m_name = json["name"].as_string();
        }
        else
        {
            info->m_name = "<none>";
        }
        
        if(json.has_key("objects") && json["objects"].is_array())
        {
            for (auto &elem : json["objects"].as_array())
            {
                auto objInfo = ContentLevelObjectInfo::FromJSON(elem);
                assert (objInfo != nullptr);

                info->m_objects.push_back(std::move(objInfo));
            }
        }

        return info;
    }

    return nullptr;
}

const std::string SerialisationUtils::IntTypeStr = "Integer";
const std::string SerialisationUtils::FloatTypeStr = "Float";
const std::string SerialisationUtils::Vector2TypeStr = "Vec2";
const std::string SerialisationUtils::Vector3TypeStr = "Vec3";
const std::string SerialisationUtils::Vector4TypeStr = "Vec4";
const std::string SerialisationUtils::Texture2DTypeStr = "Texture2D";

bool SerialisationUtils::BoolFromString(const std::string &str)
{
    if(str == "true" || str == "1")
    {
        return true; 
    }

    if(str == "false" || str == "0")
    {
        return false;
    }

    throw std::invalid_argument("String value does not contain valid boolean value!");
}

Vec2 SerialisationUtils::Vec2FromString(const std::string &str)
{
    std::vector<std::string> tokens = SerialisationUtils::SplitString(str, ',');
    if(tokens.size() == 2)
    {
        float x = SerialisationUtils::FloatFromString(tokens[0]);
        float y = SerialisationUtils::FloatFromString(tokens[1]);

        return Vec2(x, y);
    }
    else
    {
        throw std::invalid_argument("String does not contain 2 items delimited by comma");
    }
}

Vec3 SerialisationUtils::Vec3FromString(const std::string &str)
{
    std::vector<std::string> tokens = SerialisationUtils::SplitString(str, ',');
    if(tokens.size() == 3)
    {
        float x = SerialisationUtils::FloatFromString(tokens[0]);
        float y = SerialisationUtils::FloatFromString(tokens[1]);
        float z = SerialisationUtils::FloatFromString(tokens[2]);

        return Vec3(x, y, z);
    }
    else
    {
        throw std::invalid_argument("String does not contain 3 items delimited by comma");
    }
}

Vec4 SerialisationUtils::Vec4FromString(const std::string &str)
{
    std::vector<std::string> tokens = SerialisationUtils::SplitString(str, ',');
    if(tokens.size() == 4)
    {
        float x = SerialisationUtils::FloatFromString(tokens[0]);
        float y = SerialisationUtils::FloatFromString(tokens[1]);
        float z = SerialisationUtils::FloatFromString(tokens[2]);
        float w = SerialisationUtils::FloatFromString(tokens[3]);

        return Vec4(x, y, z, w);
    }
    else
    {
        throw std::invalid_argument("String does not contain 4 items delimited by comma");
    }
}

std::vector<std::string> SerialisationUtils::SplitString(const std::string &str, const char delimiter)
{
    std::vector<std::string> splits;
    std::istringstream ss(str);
    std::string token;

    while(std::getline(ss,token, delimiter ))
    {
        splits.push_back(token);
    }

    return splits;
}

float SerialisationUtils::FloatFromString(const std::string &str)
{
    float val;
    try
    {
        val = stof(str);
    }
    catch(const std::exception& e)
    {
        throw std::invalid_argument("String value does not contain a float number !");
    }
    
    return val;
}

int SerialisationUtils::IntFromString(const std::string &str)
{
    int val;
    try
    {
        val = stoi(str);
    }
    catch(const std::exception& e)
    {
        throw std::invalid_argument("String value does not contain an integer number !");
    }
    
    return val;
}

SerialisationUtils::ValueType SerialisationUtils::GetTypeFromTypeString(const std::string &str)
{
    // TODO:
    // This is awfully explicit 
    // Need to find a better way to handle value types coming from text

    if(str == IntTypeStr)
    {
        return SerialisationUtils::ValueType::Int;
    }

    if(str == FloatTypeStr)
    {
        return SerialisationUtils::ValueType::Float;
    }

    if(str == Vector2TypeStr)
    {
        return SerialisationUtils::ValueType::Vector2;
    }

    if(str == Vector3TypeStr)
    {
        return SerialisationUtils::ValueType::Vector3;
    }

    if(str == Vector4TypeStr)
    {
        return SerialisationUtils::ValueType::Vector4;
    }

    if(str == Texture2DTypeStr)
    {
        return SerialisationUtils::ValueType::Texture2D;
    }

    return SerialisationUtils::ValueType::Unknown;
}
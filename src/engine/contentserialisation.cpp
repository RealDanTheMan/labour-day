#include "contentserialisation.hpp"
#include <iostream>

using namespace Engine;

std::unique_ptr<ContentMaterialInfo> ContentMaterialInfo::FromJSON(const configuru::Config &json)
{
    if(json.has_key("type") && json["type"] == "Material")
    {
        auto info = std::make_unique<ContentMaterialInfo>();
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
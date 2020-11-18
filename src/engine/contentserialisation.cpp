#include "contentserialisation.hpp"

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
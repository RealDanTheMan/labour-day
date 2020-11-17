#ifndef CONTENT_SERIALISER_HPP_
#define CONTENT_SERIALISER_HPP_

#include "meshgen.hpp"
#include "model.hpp"
#include "material.hpp"
#include "texture2d.hpp"
#include "prefab.hpp"
#include "sysutils.hpp"

namespace Engine
{
    struct ContentModelInfo
    {
        public:
        
        std::string m_name;
        std::string m_meshKey;
        std::string m_materialKey;

        static std::unique_ptr<ContentModelInfo> FromJSON(const configuru::Config &json);
    };

    struct ContentMaterialInfo
    {
        public:

        std::string m_name;
        std::string m_shaderKey;

        static std::unique_ptr<ContentMaterialInfo> FromJSON(const configuru::Config &json);
    };

    struct ContentPropertyInfo
    {
        std::string m_name;
        std::string m_value;
        std::string m_type;

        static std::unique_ptr<ContentPropertyInfo> FromJSON(const configuru::Config &json);
    };

    struct ContentPrefabComponentInfo
    {
        public:
        
        std::string m_type;
        std::string m_name;
        std::vector<std::unique_ptr<ContentPropertyInfo>> m_properties;

        static std::unique_ptr<ContentPrefabComponentInfo> FromJSON(const configuru::Config &json);
    };

    struct ContentPrefabInfo
    {
        public:

        std::string m_name;
        std::vector<std::unique_ptr<ContentPrefabComponentInfo>> m_components;

        static std::unique_ptr<ContentPrefabInfo> FromJSON(const configuru::Config &json);
    };

    class ContentSerialiser
    {
        public:

        static std::unique_ptr<Mesh> LoadMesh(const std::string &filepath);
        static std::unique_ptr<ContentMaterialInfo> LoadMaterialInfo(const std::string &filepath);
        static std::unique_ptr<ContentModelInfo> LoadModelInfo(const std::string &filepath);
        static std::unique_ptr<ContentPrefabInfo> LoadPrefabInfo(const std::string &filepath);
    };
}

#endif
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

    struct ContentPrefabInfo
    {
        std::string m_name;
        std::vector<std::unique_ptr<ContentPrefabComponentInfo>> m_components;

        static std::unique_ptr<ContentPrefabInfo> FromJSON(const configuru::Config &json);
    };

    struct ContentPrefabComponentInfo
    {
        std::string m_type;
        std::string m_name;

        static std::unique_ptr<ContentPrefabComponentInfo> FromJSON(const configuru::Config &json);
    };

    class ContentSerialiser
    {
        public:

        static std::unique_ptr<Mesh> LoadMesh(const std::string &filepath);
        static std::unique_ptr<Prefab> LoadPrefab(const std::string &filepath);

        static std::unique_ptr<ContentMaterialInfo> LoadMaterialInfo(const std::string &filepath);
        static std::unique_ptr<ContentModelInfo> LoadModelInfo(const std::string &filepath);
        static std::unique_ptr<ContentPrefabInfo> LoadEntityInfo(const std::string &filepath);
    };
}

#endif
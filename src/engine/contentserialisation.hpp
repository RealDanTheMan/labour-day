#ifndef CONTENT_SERIALISATION_HPP_
#define CONTENT_SERIALISATION_HPP_

#include "sysutils.hpp"
#include "types.hpp"
#include "../external/configuru.hpp"

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

    struct ContentEntityComponentInfo
    {
        public:
        
        std::string m_type;
        std::string m_name;
        std::vector<std::unique_ptr<ContentPropertyInfo>> m_properties;

        static std::unique_ptr<ContentEntityComponentInfo> FromJSON(const configuru::Config &json);
    };

    struct ContentEntityInfo
    {
        public:

        std::string m_name;
        std::vector<std::unique_ptr<ContentEntityComponentInfo>> m_components;
        std::vector<std::unique_ptr<ContentEntityInfo>> m_children;

        static std::unique_ptr<ContentEntityInfo> FromJSON(const configuru::Config &json);
    };

    struct ContentManifestInfo
    {
        public:

        std::map<std::string, std::string> m_meshes;
        std::map<std::string, std::string> m_textures;
        std::map<std::string, std::string> m_materials;
        std::map<std::string, std::string> m_models;
        std::map<std::string, std::string> m_prefabs;

        static std::unique_ptr<ContentManifestInfo> FromJSON(const configuru::Config &json);
        void Printout() const;
    };

    class SerialisationUtils 
    {
        public:
        static bool BoolFromString (const std::string &str);
        static Vec2 Vec2FromString(const std::string &str);
        static Vec3 Vec3FromString(const std::string &str);
        static Vec4 Vec4FromString(const std::string &str);

        static std::vector<std::string> SplitString(const std::string &str, const char delimiter);
        static float FloatFromString(const std::string &str);
    };
}

#endif
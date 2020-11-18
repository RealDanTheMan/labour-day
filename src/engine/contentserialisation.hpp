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

        static std::unique_ptr<ContentEntityInfo> FromJSON(const configuru::Config &json);
    };
}

#endif
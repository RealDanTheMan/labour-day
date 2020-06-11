#ifndef ENTITY_COMPONENT_HPP_
#define ENTITY_COMPONENT_HPP_

#include "types.hpp"
#include <string>
#include <map>

namespace Engine
{
    struct EntityComponentDesc
    {
        uint32_t m_classID;
        std::string m_className;
    };

    class EntityComponent
    {
        public:
            virtual void Init()=0;
            virtual const EntityComponentDesc& Desc()=0;
    };

    class EntityComponentFac
    {
        public:
        static bool RegieterClass(const EntityComponentDesc &classDesc);

        private:
        static std::map<std::string, EntityComponentDesc> m_map;
    };
}

#endif

#ifndef ENTITY_SERIALISER_HPP_
#define ENTITY_SERIALISER_HPP_

#include "../external/configuru.hpp"
#include "entity.hpp"
#include <string>

namespace Engine
{
    class EntityComponentSerialiser
    {
        public:
        EntityComponentSerialiser(const std::string &className);
        virtual ~EntityComponentSerialiser();
        virtual bool Deserialise(EntityComponent* pComponent, const configuru::Config &json) const;
        virtual bool DeserialiseAdd(Entity* pEntity, const configuru::Config &json) const;

        public:
        std::string m_className;
    };

    class EntitySerialiser
    {
        public:
        static void RegisterComponentSerialiser(const EntityComponentSerialiser &serialiser);
        static std::unique_ptr<Entity> Deserialise(const configuru::Config &json);

        private:
        static const EntityComponentSerialiser * const GetComponentSerialiser(const std::string className);
        static void DeserialiserEntityComponent(Entity *pEntity, const EntityComponentSerialiser *pSerialiser);

        private:
        static std::map<std::string, EntityComponentSerialiser> m_cmpSerialisers;
    };
}

#endif
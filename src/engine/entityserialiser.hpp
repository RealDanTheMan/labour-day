#ifndef ENTITY_SERIALISER_HPP_
#define ENTITY_SERIALISER_HPP_

#include "contentserialisation.hpp"
#include "entity.hpp"
#include <string>

namespace Engine
{
    class EntityComponentSerialiser
    {
        public:
        EntityComponentSerialiser(const std::string &className);
        virtual ~EntityComponentSerialiser();
        
        const std::string &ClassName() const;
        virtual bool Deserialise(EntityComponent* pComponent, const ContentEntityComponentInfo * sourceContent) const =0;
        virtual bool DeserialiseAdd(Entity* pEntity, const ContentEntityComponentInfo * sourceContent) const =0;

        private:
        std::string m_className;
    };

    class EntitySerialiser
    {
        public:
        template <typename T>
        static void RegisterComponentSerialiser();
        static const EntityComponentSerialiser * const GetComponentSerialiser(const std::string className);
        static std::vector<std::unique_ptr<Entity>> Deserialise(const ContentEntityInfo * sourceContent);

        private:
        static void DeserialiserEntityComponent(Entity *pEntity, const EntityComponentSerialiser *pSerialiser, const ContentEntityComponentInfo * pComponentInfo);

        private:
        static std::map<std::string, std::unique_ptr<EntityComponentSerialiser>> m_cmpSerialisers;
    };

    template <typename T>
    void EntitySerialiser::RegisterComponentSerialiser()
    {
        static_assert (std::is_base_of<EntityComponentSerialiser, T>::value, "Invalid template type, expected derived from <EntityComponentSerialiser>");
        auto pSerialiser = std::make_unique<T>();

        assert (EntitySerialiser::m_cmpSerialisers.find(pSerialiser->ClassName()) == EntitySerialiser::m_cmpSerialisers.end());
        EntitySerialiser::m_cmpSerialisers.insert(std::make_pair(pSerialiser->ClassName(), std::move(pSerialiser)));
    }
}

#endif
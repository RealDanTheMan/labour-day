#include "entityserialiser.hpp"

#define CONFIGURU_IMPLEMENTATION 1
#include "../external/configuru.hpp"

using namespace Engine;


EntityComponentSerialiser::~EntityComponentSerialiser()
{
}

bool EntityComponentSerialiser::Deserialise(EntityComponent* pComponent, const configuru::Config &json) const
{
    return false;
}

bool EntityComponentSerialiser::DeserialiseAdd(Entity* pEntity, const configuru::Config &json) const
{
    return false;
}


std::map<std::string, EntityComponentSerialiser> EntitySerialiser::m_cmpSerialisers = {};

void EntitySerialiser::RegisterComponentSerialiser(const EntityComponentSerialiser serialiser)
{
    assert (EntitySerialiser::m_cmpSerialisers.find(serialiser.m_className) != EntitySerialiser::m_cmpSerialisers.end());
    EntitySerialiser::m_cmpSerialisers.insert(std::make_pair(serialiser.m_className, serialiser));
}

std::unique_ptr<Entity> EntitySerialiser::Deserialise (const configuru::Config &json)
{
    if(json.has_key("type") && json["type"] == "Entity")
    {
        auto pEntity = std::make_unique<Entity>();

        if(json.has_key("components") && json["components"].is_array())
        {
            for (const configuru::Config& element : json["components"].as_array()) 
            {
                assert (element.has_key("type"));
                std::string className = (std::string)element["type"];
                const EntityComponentSerialiser *cmpSerialiser = EntitySerialiser::GetComponentSerialiser(className);
                assert (cmpSerialiser != nullptr);
                EntitySerialiser::DeserialiserEntityComponent(pEntity.get(), cmpSerialiser);
            }
        }


        return pEntity;
    }

    return nullptr;
}

const EntityComponentSerialiser * const EntitySerialiser::GetComponentSerialiser(const std::string className)
{
    return nullptr;
}

void EntitySerialiser::DeserialiserEntityComponent(Entity *pEntity, const EntityComponentSerialiser *pSerialiser)
{
    assert (pEntity != nullptr);
    assert (pSerialiser != nullptr);

}
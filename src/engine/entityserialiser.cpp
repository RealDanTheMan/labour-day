#include "entityserialiser.hpp"
#include "debugging.hpp"

#define CONFIGURU_IMPLEMENTATION 1
#include "../external/configuru.hpp"

using namespace Engine;

EntityComponentSerialiser::EntityComponentSerialiser(const std::string &className):
m_className(className)
{
}


EntityComponentSerialiser::~EntityComponentSerialiser()
{
}

const std::string& EntityComponentSerialiser::ClassName() const
{
    return m_className;
}

std::map<std::string, std::unique_ptr<EntityComponentSerialiser>> EntitySerialiser::m_cmpSerialisers = {};

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
                EntitySerialiser::DeserialiserEntityComponent(pEntity.get(), cmpSerialiser, element);
            }
        }


        return pEntity;
    }

    return nullptr;
}

const EntityComponentSerialiser * const EntitySerialiser::GetComponentSerialiser(const std::string className)
{
    assert (m_cmpSerialisers.find(className) != m_cmpSerialisers.end());
    return m_cmpSerialisers.at(className).get();
}

void EntitySerialiser::DeserialiserEntityComponent(Entity *pEntity, const EntityComponentSerialiser *pSerialiser, const configuru::Config &json)
{
    assert (pEntity != nullptr);
    assert (pSerialiser != nullptr);

    bool deserialised = pSerialiser->DeserialiseAdd(pEntity, json);
    assert (deserialised);
}
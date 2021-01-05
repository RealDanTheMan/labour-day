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

std::vector<std::unique_ptr<Entity>> EntitySerialiser::Deserialise (const ContentEntityInfo * sourceContent)
{
    std::vector<std::unique_ptr<Entity>> all;

    auto pEntity = std::make_unique<Entity>();
    for (uint32_t i=0; i < sourceContent->m_components.size(); i++)
    {
        std::string className = sourceContent->m_components[i]->m_type;
        const EntityComponentSerialiser *cmpSerialiser = EntitySerialiser::GetComponentSerialiser(className);
        assert (cmpSerialiser != nullptr);
        EntitySerialiser::DeserialiserEntityComponent(pEntity.get(), cmpSerialiser, sourceContent->m_components[i].get());
    }

    for(auto& childInfo : sourceContent->m_children)
    {
        std::vector<std::unique_ptr<Entity>> children = Deserialise(childInfo.get());
        for(auto &child : children)
        {
            child->SetParent(pEntity.get());
            all.push_back(std::move(child));
        }
    }

    all.push_back(std::move(pEntity));
    return all;
}

const EntityComponentSerialiser * const EntitySerialiser::GetComponentSerialiser(const std::string className)
{
    assert (m_cmpSerialisers.find(className) != m_cmpSerialisers.end());
    return m_cmpSerialisers.at(className).get();
}

void EntitySerialiser::DeserialiserEntityComponent(Entity *pEntity, const EntityComponentSerialiser *pSerialiser, const ContentEntityComponentInfo * pComponentInfo)
{
    assert (pEntity != nullptr);
    assert (pSerialiser != nullptr);

    bool deserialised = pSerialiser->DeserialiseAdd(pEntity, pComponentInfo);
    assert (deserialised);
}
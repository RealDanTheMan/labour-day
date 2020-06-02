#include "entityserialiser.hpp"

#define CONFIGURU_IMPLEMENTATION 1
#include "../external/configuru.hpp"

using namespace Engine;

std::unique_ptr<Entity> EntitySerialiser::Deserialise (const configuru::Config &json)
{
    if(json.has_key("type") && json["type"] == "entity")
    {
        auto pEntity = std::make_unique<Entity>();

        if(json.has_key("components") && json["components"].is_array())
        {
            for (const configuru::Config& element : json["components"].as_array()) 
            {
                
            }
        }


        return pEntity;
    }

    return nullptr;
}
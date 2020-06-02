#ifndef ENTITY_SERIALISER_HPP_
#define ENTITY_SERIALISER_HPP_

#include "../external/configuru.hpp"
#include "entity.hpp"

namespace Engine
{
    class EntitySerialiser
    {
        public:
        static std::unique_ptr<Entity> Deserialise(const configuru::Config &json);
    };
}

#endif
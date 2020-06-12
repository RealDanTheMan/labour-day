#ifndef ENTITY_COMPONENT_HPP_
#define ENTITY_COMPONENT_HPP_

#include "types.hpp"
#include <string>
#include <map>

namespace Engine
{

    class EntityComponent
    {
        public:
            virtual void Init()=0;
    };
}

#endif

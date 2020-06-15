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
            virtual ~EntityComponent();
            virtual void Init()=0;
            virtual std::unique_ptr<EntityComponent> Duplicate() const =0;
    };
}

#endif

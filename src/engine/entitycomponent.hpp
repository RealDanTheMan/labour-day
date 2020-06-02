#ifndef ENTITY_COMPONENT_HPP_
#define ENTITY_COMPONENT_HPP_

namespace Engine
{
    class EntityComponent
    {
        public:
            EntityComponent();
            EntityComponent(const EntityComponent &rhs);

            virtual void Init()=0;;
    };
}

#endif

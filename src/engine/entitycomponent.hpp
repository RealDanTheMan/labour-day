#ifndef ENTITY_COMPONENT_HPP_
#define ENTIRY_COMPONENT_HPP_

namespace Engine
{
    class EntityComponent
    {
        public:
            EntityComponent();
            EntityComponent(const EntityComponent &rhs);

            virtual void Init();
            virtual void Update();
    };
}

#endif

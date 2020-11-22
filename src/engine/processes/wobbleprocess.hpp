#ifndef WOBBLE_PROCESS_HPP_
#define WOBBLE_PROCESS_HPP_

#include "../entityprocess.hpp"

namespace Engine::Processes
{
    class WobbleProcess : public EntityProcess
    {
        public:

        void OnUpdate(Entity * const entity) override;

        private:
        virtual bool IsValidEntity(Entity * const Entity) override;
    };
}

#endif
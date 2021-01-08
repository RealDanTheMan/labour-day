#ifndef MOVEMENT_PROCESS_HPP_
#define MOVEMENT_PROCESS_HPP_

#include "../entityprocess.hpp"

namespace Engine
{
    namespace Processes
    {
        class MovementProcess : public Engine::EntityProcess
        {
            public:
            MovementProcess() = default;
            MovementProcess(const MovementProcess &rhs) = default;

            virtual void OnUpdate(Entity * const entity) override;

            private:
            virtual bool IsValidEntity(Entity * const entity) override;
        };
    }
}

#endif
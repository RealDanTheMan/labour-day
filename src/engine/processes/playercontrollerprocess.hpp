#ifndef PLAYER_CONTROLLER_PROCESS_HPP_
#define PLAYER_CONTROLLER_PROCESS_HPP_

#include "../entityprocess.hpp"

namespace Engine
{
    namespace Processes
    {
        class PlayerControllerProcess : public Engine::EntityProcess
        {
            public:
            PlayerControllerProcess() = default;
            PlayerControllerProcess(const PlayerControllerProcess &rhs) = default;

            virtual void OnUpdate(Entity * const entity) override;

            private:
            virtual bool IsValidEntity(Entity * const entity) override;
        };
    }
}

#endif
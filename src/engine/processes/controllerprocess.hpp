#ifndef CONTROLLER_PROCESS_HPP_
#define CONTROLLER_PROCESS_HPP_

#include "../entityprocess.hpp"

namespace Engine
{
    namespace Processes
    {
        class ControllerProcess : public EntityProcess
        {
            public:
            ControllerProcess() = default;
            ControllerProcess(const ControllerProcess &rhs) = default;

            virtual void OnUpdate(Entity * const entity) override;
            
            private:
            virtual bool IsValidEntity(Entity * const entity) override;
        };
    }
}

#endif
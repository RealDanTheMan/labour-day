#ifndef ENGINECORE_H_
#define ENGINECORE_H_

#include "glfwinterface.hpp"
#include <memory>

namespace Engine
{
    class EngineCore
    {
        private:
        std::unique_ptr<GLFWInterface> m_glfw;

        public:
        EngineCore();
        bool Initialize();
        void Terminate();
    };
}

#endif
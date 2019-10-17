#ifndef GLFWINTERFACE_HPP_
#define GLFWINTERFACE_HPP_

#include <GLFW/glfw3.h>

namespace Engine
{
    class GLFWInterface 
    {
        public:
        static void ErrCallback(int err, const char* msg);
        
        bool Initialize();
        void Terminate();
        const bool Initialized() const;

        private:
        bool m_initialized;
    };
}

#endif
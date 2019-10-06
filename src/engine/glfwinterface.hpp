#ifndef GLFWINTERFACE_H_
#define GLFWINTERFACE_H_

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
#ifndef SHADERPROG_H_
#define SHADERPROG_H_

#include "shadersource.hpp"
#include <string>

namespace Engine
{
    class ShaderProg
    {
        public:

        ShaderProg(const ShaderSource &vs, const ShaderSource &ps);
        void Free();
        const bool Ready() const;
        const std::string GetLog() const;

        private:

        GLuint m_handle;
        bool m_ready; 
    };
}

#endif
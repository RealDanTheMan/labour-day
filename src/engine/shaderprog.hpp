#ifndef SHADERPROG_HPP_
#define SHADERPROG_HPP_

#include "shadersemantics.hpp"
#include "shadersource.hpp"
#include "shaderparamcollection.hpp"
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
        const GLuint GetHandle() const;
        ShaderParamCollection * const ShaderParameters() const;

        private:
        std::unique_ptr<ShaderParamCollection> m_params;
        GLuint m_handle;
        bool m_ready; 
    };
}

#endif
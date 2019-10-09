#ifndef SHADERSOURCE_H_
#define SHADERSOURCE_H_

#include "glewinterface.hpp"
#include <string>

namespace Engine
{
    class ShaderSource
    {
        public:

        enum ShaderSourceType 
        {
            Vertex,
            Pixel,
            Geometry
        };

        ShaderSource(const std::string &src, const ShaderSourceType &type);
        void Compile();
        void Free();
        const bool Compiled() const;
        const std::string GetLog() const;
        const ShaderSourceType GetType() const;
        const GLuint GetHandle() const;

        private:

        const char* m_source;
        int m_len;
        ShaderSourceType m_type;
        GLuint m_handle;
        bool m_compiled;
    };
}

#endif
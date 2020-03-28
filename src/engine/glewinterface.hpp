#ifndef GLEWINTERFACE_HPP_
#define GLEWINTERFACE_HPP_

#include <GL/glew.h>

namespace Engine
{
    class GLEWInterface
    {
        public:
        static void ErrCallback(GLenum source,
                 GLenum type,
                 GLuint id,
                 GLenum severity,
                 GLsizei length,
                 const GLchar* msg,
                 const void* userParam);

        bool Initialize();
    };
}

#endif
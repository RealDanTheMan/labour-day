#ifndef GLEWINTERFACE_H_
#define GLEWINTERFACE_H_

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
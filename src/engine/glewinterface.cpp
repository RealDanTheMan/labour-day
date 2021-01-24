#include "glewinterface.hpp"
#include <stdio.h>

using namespace Engine;

bool GLEWInterface::Initialize()
{
    glewExperimental = true;
    if(glewInit() == GLEW_OK)
    {
        glDebugMessageCallback(GLEWInterface::ErrCallback, nullptr);
        return true;
    }

    return false;
}

void GLEWInterface::ErrCallback( GLenum source,
                 GLenum type,
                 GLuint id,
                 GLenum severity,
                 GLsizei length,
                 const GLchar* msg,
                 const void* userParam )
{
    if(id == 131185)
    {
        // Skip buffer detailed info output message spamming the console
        return;
    }
    
    fprintf(stderr, "GL Error: %d -> %s \n", id, msg);
}
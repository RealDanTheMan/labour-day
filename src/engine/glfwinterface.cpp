#include "glfwinterface.hpp"
#include <stdio.h>

using namespace Engine;

bool GLFWInterface::Initialize()
{
    glfwSetErrorCallback(GLFWInterface::ErrCallback);
    if(glfwInit() == GLFW_TRUE)
    {
        m_initialized = true;
        return true;
    }

    return false;
}

void GLFWInterface::Terminate()
{
    glfwTerminate();
    m_initialized = false;
}

const bool GLFWInterface::Initialized() const
{
    return m_initialized;
}

void GLFWInterface::ErrCallback(int err, const char* msg)
{
    fprintf(stderr, "GLFW Error: %d -> %s \n", err, msg);
}
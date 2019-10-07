#include "glewinterface.hpp"

using namespace Engine;

bool GLEWInterface::Initialize()
{
    glewExperimental = true;
    if(glewInit() == GLEW_OK)
    {
        return true;
    }

    return false;
}
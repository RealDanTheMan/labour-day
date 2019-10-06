#include <GLFW/glfw3.h>
#include "engine/glfwinterface.hpp"
#include "engine/enginecore.hpp"
#include "engine/window.hpp"

#include <assert.h>

int main()
{

    Engine::EngineCore core = Engine::EngineCore();
    Engine::EngineCoreSettings settings = Engine::EngineCoreSettings();
    settings.m_windowWidth = 1280;
    settings.m_windowHeight = 720;

    if(!core.Initialize(settings))
    {
        fprintf(stderr, "Failed to initialize engine core !\n");
    }

    while(core.MainWindowActive())
    {
        core.RedrawMainWindow();
    }

    core.Terminate();
    
    return 0;
}
#include <GLFW/glfw3.h>
#include "engine/glfwinterface.hpp"
#include "engine/enginecore.hpp"
#include "engine/window.hpp"

int main()
{
    Engine::EngineCore core = Engine::EngineCore();
    core.Initialize();

    std::unique_ptr<Engine::Window> win = std::make_unique<Engine::Window>();
    while(win->Ready())
    {
    }

    core.Terminate();
    
    return 0;
}
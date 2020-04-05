#include "app.hpp"
#include "engine/debugging.hpp"
#include "engine/meshgen.hpp"
#include "engine/renderable.hpp"
#include "engine/runtimeshaders.hpp"
#include "engine/camera.hpp"

#include <memory>

int main()
{
    D_MSG("Runing app ...");

    App app = App();
    if(!app.Initialize())
    {
        D_ERR("Failed to initialize app !");
        return 1;
    }

    app.Run();
    app.Exit();

    D_MSG("Exiting app ...");
    
    return 0;
}
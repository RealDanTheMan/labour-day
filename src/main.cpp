#include "app.hpp"
#include "engine/debugging.hpp"

int main()
{
    D_MSG("Runing app ...");

    App app = App();
    if(!app.Initialize())
    {
        D_ERR("Failed to initialize engine core !");
        return 1;
    }

    app.Run();
    app.Exit();

    D_MSG("Exiting app ...");
    
    return 0;
}
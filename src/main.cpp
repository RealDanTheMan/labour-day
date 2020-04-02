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

    Engine::Camera cam;

    std::unique_ptr<Engine::RuntimeShaders> shaders = std::make_unique<Engine::RuntimeShaders>();
    shaders->Init();
    assert (shaders->Ready());
    
    std::unique_ptr<Engine::Mesh> msh = Engine::MeshGen::Triangle(1.0f);
    std::unique_ptr<Engine::Renderable> tri = std::make_unique<Engine::Renderable>();
    tri->Init(msh->Vertices(), msh->Indices(), msh->VertexCount(), msh->IndexCount());
    tri->BindShader(shaders->FlatWhite());

    assert (tri->Ready());
    app.Engine()->Renderer()->SetCamera(&cam);
    app.Engine()->Renderer()->AddToQueue(tri.get());

    app.Run();
    app.Exit();

    D_MSG("Exiting app ...");
    
    return 0;
}
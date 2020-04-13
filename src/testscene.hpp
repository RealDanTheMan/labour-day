#ifndef TEST_SCENE_HPP_
#define TEST_SCENE_HPP_

#include "engine/enginecore.hpp"
#include "engine/renderable.hpp"
#include "engine/entity.hpp"

class TestScene
{
    private:
    std::unique_ptr<Engine::Renderable> m_triangle;
    std::unique_ptr<Engine::Entity> m_asset;
    std::unique_ptr<Engine::Camera> m_camera;
    Engine::EngineCore* m_core;

    public:
    void Initialize(Engine::EngineCore *core);
    void Update();

    Engine::Renderable* TestTriangle();
    Engine::Entity* Asset();
    Engine::Camera* Cam();

};

#endif
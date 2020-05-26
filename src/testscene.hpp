#ifndef TEST_SCENE_HPP_
#define TEST_SCENE_HPP_

#include "engine/enginecore.hpp"
#include "engine/renderable.hpp"
#include "engine/model.hpp"
#include "engine/entity.hpp"
#include "engine/gltex.hpp"
#include "engine/assetcache.hpp"

class TestScene
{
    private:
    std::unique_ptr<Engine::AssetCache> m_cache;
    std::unique_ptr<Engine::Renderable> m_mesh;
    std::unique_ptr<Engine::Model> m_model;
    std::unique_ptr<Engine::Material> m_mat;
    std::unique_ptr<Engine::Camera> m_camera;
    
    Engine::EngineCore* m_core;
    Engine::Entity* m_asset;

    public:
    void Initialize(Engine::EngineCore *core);
    void Update();
    void Free();

    Engine::Renderable* TestTriangle();
    Engine::Entity* Asset();
    Engine::Camera* Cam();

};

#endif
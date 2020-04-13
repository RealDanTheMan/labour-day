#ifndef TEST_ENTITY_HPP_
#define TEST_ENTITY_HPP_

#include "engine/entity.hpp"
#include <memory>

class TestComponent : public Engine::EntityComponent
{
    public:

    void Init() override;
    void Update() override;
};

class TestEntity
{
    public:
    static std::unique_ptr<Engine::Entity> Create();
};

#endif
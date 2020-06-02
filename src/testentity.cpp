#include "testentity.hpp"
#include "engine/debugging.hpp"
#include "engine/components/modelcomponent.hpp"

std::unique_ptr<Engine::Entity> TestEntity::Create()
{
    auto entity = std::make_unique<Engine::Entity>();
    auto com = entity->Components().Add<Engine::Components::ModelComponent>();

    assert (com != nullptr);

    return entity;
}
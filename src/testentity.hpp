#ifndef TEST_ENTITY_HPP_
#define TEST_ENTITY_HPP_

#include "engine/entity.hpp"
#include <memory>


class TestEntity
{
    public:
    static std::unique_ptr<Engine::Entity> Create();
};

#endif
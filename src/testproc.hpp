#ifndef TEST_PROC_HPP_
#define TEST_PROC_HPP_

#include "engine/entityprocess.hpp"

class TestProc : public Engine::EntityProcess
{
    public:
    float m_speed;

    public:
    TestProc();
    virtual void OnUpdate (Engine::Entity * const entity) override;
};

#endif
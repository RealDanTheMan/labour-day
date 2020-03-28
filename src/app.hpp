#ifndef APP_HPP_
#define APP_HPP_

#include "engine/enginecore.hpp"

class App
{
    public:
    bool Initialize();
    void Run();
    void Exit();
    Engine::EngineCore* Engine();

    private:
    std::unique_ptr<Engine::EngineCore> m_core;
};

#endif
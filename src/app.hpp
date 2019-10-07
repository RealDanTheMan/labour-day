#ifndef APP_H_
#define APP_H_

#include "engine/enginecore.hpp"

class App
{
    public:
    bool Initialize();
    void Run();
    void Exit();

    private:
    std::unique_ptr<Engine::EngineCore> m_core;
};

#endif
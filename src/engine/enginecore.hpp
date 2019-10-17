#ifndef ENGINECORE_HPP_
#define ENGINECORE_HPP_

#include "glewinterface.hpp"
#include "glfwinterface.hpp"
#include "window.hpp"
#include <memory>

namespace Engine
{
    struct EngineCoreSettings
    {
        uint32_t m_windowWidth;
        uint32_t m_windowHeight;
    };

    class EngineCore
    {
        private:
        std::unique_ptr<GLEWInterface> m_glew;
        std::unique_ptr<GLFWInterface> m_glfw;
        std::unique_ptr<Window> m_mainWin;

        public:
        EngineCore();
        bool Initialize();
        bool Initialize(const EngineCoreSettings &settings);
        void Terminate();
        void RedrawMainWindow();
        const bool MainWindowActive() const;
    };
}

#endif
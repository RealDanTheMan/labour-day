#ifndef ENGINECORE_H_
#define ENGINECORE_H_

#include "glewinterface.hpp"
#include "glfwinterface.hpp"
#include "window.hpp"
#include "commonrenderer.hpp"
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
        std::unique_ptr<CommonRenderer> m_renderer;

        public:
        EngineCore();
        bool Initialize();
        bool Initialize(const EngineCoreSettings &settings);
        void Terminate();
        void RedrawMainWindow();
        const bool MainWindowActive() const;
        CommonRenderer* Renderer();
    };
}

#endif
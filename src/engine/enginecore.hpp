#ifndef ENGINECORE_HPP_
#define ENGINECORE_HPP_

#include "glewinterface.hpp"
#include "glfwinterface.hpp"
#include "window.hpp"
#include "commonrenderer.hpp"
#include "runtimeshaders.hpp"
#include "gfx.hpp"
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
        std::unique_ptr<GLFWInterface> m_glfw;
        std::unique_ptr<Gfx> m_gfx;
        std::unique_ptr<Window> m_mainWin;
        std::unique_ptr<CommonRenderer> m_renderer;
        std::unique_ptr<RuntimeShaders> m_runtimeShaders;

        public:
        EngineCore();
        bool Initialize();
        bool Initialize(const EngineCoreSettings &settings);
        void Terminate();
        void RedrawMainWindow();
        void ClearMainWindow();
        void PresentMainWindow();
        const bool MainWindowActive() const;
        CommonRenderer* Renderer();
        RuntimeShaders* Shaders() const;
    };
}

#endif
#ifndef ENGINECORE_HPP_
#define ENGINECORE_HPP_

#include "glewinterface.hpp"
#include "glfwinterface.hpp"
#include "window.hpp"
#include "commonrenderer.hpp"
#include "runtimeshaders.hpp"
#include "gfx.hpp"
#include "ecssys.hpp"
#include "gametime.hpp"
#include "imguiinterface.hpp"
#include "fpscounter.hpp"
#include <memory>

#include "components/modelcomponent.hpp"
#include "components/wobblecomponent.hpp"
#include "components/cameracomponent.hpp"

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
        std::unique_ptr<ECSSys> m_ecs;
        std::unique_ptr<GameTime> m_time;
        std::unique_ptr<IMGuiInterface> m_imgui;
        std::unique_ptr<FpsCounter> m_fpsCounter;

        public:
        EngineCore();
        bool Initialize();
        bool Initialize(const EngineCoreSettings &settings);
        void Terminate();
        void RedrawMainWindow();
        void ClearMainWindow();
        void PresentMainWindow();
        void IncrementTime();
        double GetDeltaTime() const;
        double GetGameTime() const;
        const bool MainWindowActive() const;
        CommonRenderer* Renderer();
        RuntimeShaders* Shaders() const;
        ECSSys* ECS() const;
        const GameTime * const Time() const;
        IMGuiInterface * IMGui() const;
        FpsCounter * const FPS() const;

        private:
        void RegisterStdComponents();
    };
}

#endif
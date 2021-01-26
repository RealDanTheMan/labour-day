#ifndef DEBUG_OVERLAY_HPP_
#define DEBUG_OVERLAY_HPP_

#include "enginecore.hpp"

namespace Engine
{
    class DebugOverlay : public IMGuiPanel
    {
        public:
        DebugOverlay(EngineCore * const engine);
        virtual void OnInit() override;
        virtual void OnUpdate() override;

        private:
        EngineCore * const m_core;

        void DrawPerfStats() const;
        void DrawCameraInfo() const;
        void DrawInputInfo() const;
        void DrawRenderSettings();

        void UpdateEngineRenderSettings();
        RenderSettings m_renderSettings;
    };
}

#endif
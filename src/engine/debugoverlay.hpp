#ifndef DEBUG_OVERLAY_HPP_
#define DEBUG_OVERLAY_HPP_

#include "enginecore.hpp"

namespace Engine
{
    class DebugOverlay : public IMGuiPanel
    {
        public:
        DebugOverlay(EngineCore * const engine);
        void OnUpdate() override;

        private:
        EngineCore * const m_core;

        void DrawPerfStats() const;
    };
}

#endif
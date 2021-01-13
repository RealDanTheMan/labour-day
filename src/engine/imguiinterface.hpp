#ifndef IMGUI_INTERFACE_HPP_
#define IMGUI_INTERFACE_HPP_

#include "../external/imgui/imgui.h"
#include "../external/imgui/backends/imgui_impl_opengl3.h"
#include "../external/imgui/backends/imgui_impl_glfw.h"

#include "window.hpp"
#include <vector>

namespace Engine
{
    class IMGuiPanel
    {
        public:
        virtual void OnInit()=0;
        virtual void OnUpdate()=0;
    };

    class IMGuiInterface
    {
        public:

        void Init(Window * win);
        void Free();
        void Update();
        void Render();
        void AddPanel(IMGuiPanel * const panel);

        private:
        ImGuiContext *m_ctx;
        std::vector<IMGuiPanel*> m_panels;
    };
}

#endif
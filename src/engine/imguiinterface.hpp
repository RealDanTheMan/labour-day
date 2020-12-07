#ifndef IMGUI_INTERFACE_HPP_
#define IMGUI_INTERFACE_HPP_

#include "../external/imgui/imgui.h"
#include "../external/imgui/backends/imgui_impl_opengl3.h"
#include "../external/imgui/backends/imgui_impl_glfw.h"

#include "window.hpp"

namespace Engine
{
    class IMGuiInterface
    {
        public:

        void Init(Window * win);
        void Free();
        void Update();
        void Render();

        private:
        ImGuiContext *m_ctx;
    };
}

#endif
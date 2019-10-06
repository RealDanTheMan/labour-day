#ifndef WINDOW_H
#define WINDOW_H

#include <stdint.h>
#include <memory>
#include <GLFW/glfw3.h>

namespace Engine
{
    struct GLFWDeleter
    {
        void operator()(GLFWwindow* ptr)
        {
            glfwDestroyWindow(ptr);
        }
    };

    class Window
    {
        public:
        Window();
        Window(const uint32_t w, const uint32_t h);

        const uint32_t GetWidth() const;
        const uint32_t GetHeight() const;
        const bool Ready() const;

        private:
        bool m_ready;
        uint32_t m_width;
        uint32_t m_height;
        std::unique_ptr<GLFWwindow, GLFWDeleter> m_winHandle;
    };
}

#endif
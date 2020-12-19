#include "window.hpp"
#include <assert.h>

using namespace Engine;

Window::Window():
m_width(128),
m_height(128),
m_winHandle(nullptr)
{
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
    glfwWindowHint(GLFW_SAMPLES, 16);
    glfwSwapInterval(0);

    GLFWwindow* raw = glfwCreateWindow(m_width, m_height, "Labour-Day", nullptr, nullptr);
    if(raw != nullptr)
    {
        m_winHandle = std::unique_ptr<GLFWwindow, GLFWWindowDeleter>(raw);
        m_ready = true;
    }
}

Window::Window(const uint32_t w, const uint32_t h):
m_width(w),
m_height(h),
m_winHandle(nullptr)
{
    assert (w > 0);
    assert (h > 0);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
    glfwWindowHint(GLFW_SAMPLES, 16);
    glfwSwapInterval(0);

    GLFWwindow* raw = glfwCreateWindow(m_width, m_height, "Labour-Day", nullptr, nullptr);
    if(raw != nullptr)
    {
        m_winHandle = std::unique_ptr<GLFWwindow, GLFWWindowDeleter>(raw);
        m_ready = true;
    }
}

const uint32_t Window::GetWidth() const
{
    return m_width;
}

const uint32_t Window::GetHeight() const
{
    return m_height;
}

const bool Window::Ready() const
{
    return m_ready && !glfwWindowShouldClose(m_winHandle.get());
}

GLFWwindow* Window::GetHandle() const
{
    return m_winHandle.get();
}
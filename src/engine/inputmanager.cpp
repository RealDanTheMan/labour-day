#include "inputmanager.hpp"
#include "debugging.hpp"
#include "glfwinterface.hpp"

using namespace Engine;

void InputManager::Initialize(const Window &win)
{
    m_keyStates = std::make_unique<bool[]>(KEY_MAX_CODE);
    glfwSetKeyCallback(win.GetHandle(), KeyCallback);
}

void InputManager::Poll()
{
    glfwPollEvents();
}

void InputManager::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    switch(action)
    {
        case GLFW_PRESS:
            InputManager::Instance().m_keyStates[key] = true;
            break;
        case GLFW_RELEASE:
            InputManager::Instance().m_keyStates[key] = false;
            break;
    }
}

const bool InputManager::CheckKey(const uint32_t keyCode) const 
{
    assert (m_keyStates != nullptr);
    assert (KEY_MAX_CODE > keyCode);

    return m_keyStates[keyCode];
}

#include "inputmanager.hpp"
#include "debugging.hpp"
#include "glfwinterface.hpp"

using namespace Engine;

void InputManager::Initialize(const Window &win)
{
    m_keyPressStates = std::make_unique<bool[]>(KEY_MAX_CODE);
    m_keyReleaseStates = std::make_unique<bool[]>(KEY_MAX_CODE);
    m_win = &win;

    //glfwSetInputMode(win.GetHandle(), GLFW_STICKY_KEYS, GLFW_TRUE);
    //glfwSetKeyCallback(win.GetHandle(), KeyCallback);
}

void InputManager::Poll()
{
    PrePoll();
    glfwPollEvents();
    PostPoll();
}

[[deprecated]]
void InputManager::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    // Dont use this anymore as key callback can get us in a reace condition when input is queried in a ECS loop
    // Get better synchorisation with direct polling
    switch(action)
    {
        case GLFW_PRESS:
            D_MSG ("KeyPress -> " + std::to_string(key));
            InputManager::Instance().m_keyPressStates[key] = true;
            InputManager::Instance().m_keyReleaseStates[key] = false;
            break;
        case GLFW_RELEASE:
            D_MSG ("KeyRelease -> " + std::to_string(key));
            InputManager::Instance().m_keyPressStates[key] = false;
            InputManager::Instance().m_keyReleaseStates[key] = true;
            break;
    }
}

InputManager::KeyState InputManager::CheckKey(const uint32_t keyCode) const 
{
    assert (m_keyPressStates != nullptr);
    assert (m_keyReleaseStates != nullptr);
    assert (KEY_MAX_CODE > keyCode);

    if(m_keyPressStates[keyCode])
    {
        return InputManager::KeyState::Active;
    }
    else if (m_keyReleaseStates[keyCode])
    {
        return InputManager::KeyState::Released;
    }
    else
    {
        return InputManager::KeyState::Inactive;
    }
}

void InputManager::PrePoll()
{
    // Clear all release codes before polling
    for (uint32_t i=0; i < KEY_MAX_CODE; i++)
    {
        m_keyReleaseStates[i] = false;
    }
}

void InputManager::PostPoll()
{
    for (uint32_t i=KEY_MIN_CODE; i < KEY_MAX_CODE; i++)
    {
        int state = glfwGetKey(m_win->GetHandle(), i);
        switch(state)
        {
            case GLFW_PRESS:
                InputManager::Instance().m_keyPressStates[i] = true;
                InputManager::Instance().m_keyReleaseStates[i] = false;
                break;
            case GLFW_RELEASE:
                InputManager::Instance().m_keyPressStates[i] = false;
                InputManager::Instance().m_keyReleaseStates[i] = true;
                break;
        }
    }
}

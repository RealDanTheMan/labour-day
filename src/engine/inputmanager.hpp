#ifndef INPUT_MANAGER_HPP_
#define INPUT_MANAGER_HPP_

#include "window.hpp"
#include "keymap.hpp"

#include <vector>

namespace Engine
{
    class InputManager
    {
        private:
        InputManager(){}

        public:
        static InputManager &Instance()
        {
            static InputManager inst;
            return inst;
        }

        enum KeyState
        {
            Inactive=0,
            Active=1,
            Released=2
        };

        void Initialize(const Window &win);
        void Poll();
        KeyState CheckKey(const uint32_t keyCode) const;
        static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

        private:
        void PrePoll();

        private:
        Window *m_win;
        std::unique_ptr<bool[]> m_keyPressStates;
        std::unique_ptr<bool[]> m_keyReleaseStates;

    };
}

#endif
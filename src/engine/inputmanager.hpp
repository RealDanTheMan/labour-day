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

        void Initialize(const Window &win);
        void Poll();
        const bool CheckKey(const uint32_t keyCode) const;
        static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

        private:
        


        private:
        Window *m_win;
        std::unique_ptr<bool[]> m_keyStates;

    };
}

#endif
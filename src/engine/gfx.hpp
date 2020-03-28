#ifndef GFX_HPP_
#define GFX_HPP_

#include "runtimeshaders.hpp"

namespace Engine
{
    class Gfx
    {
        public:
        bool Init();
        void Free();
        const RuntimeShaders* BaseShaders();

        private:
        std::unique_ptr<GLEWInterface> m_glew;
        std::unique_ptr<RuntimeShaders> m_baseShaders;
    };
}

#endif
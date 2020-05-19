#ifndef GLTEX_HPP_
#define GLTEX_HPP_

#include "glewinterface.hpp"
#include "texture2d.hpp"


namespace Engine
{
    class GLTex
    {
        public:
        GLTex(const Texture2D &tex);
        bool Ready() const;
        void Free();

        private:
        GLuint m_tex;
    };
}

#endif
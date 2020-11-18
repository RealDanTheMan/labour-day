#ifndef GLTEX_HPP_
#define GLTEX_HPP_

#include "glewinterface.hpp"


namespace Engine
{
    class GLTex
    {
        public:
        
        GLTex();
        bool Ready() const;
        void Load(const uint32_t w, const uint32_t h, unsigned char* const data);
        void Unload();
        const GLuint Handle() const;

        private:

        bool m_loaded;
        GLuint m_tex;
    };
}

#endif
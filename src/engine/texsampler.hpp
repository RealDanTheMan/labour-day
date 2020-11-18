#ifndef TEXSAMPLER_HPP_
#define TEXSAMPLER_HPP_

#include "glewinterface.hpp"

namespace Engine
{
    class TexSampler
    {
        public:
        TexSampler();

        void Init();
        void Free();
        bool Ready() const;
        const GLuint Handle() const;

        private:
        GLuint m_glHandle;
    };
}

#endif
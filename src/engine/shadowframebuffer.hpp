#ifndef SHADOW_FRAME_BUFFER_HPP_
#define SHADOW_FRAME_BUFFER_HPP_

#include "gfx.hpp"

namespace Engine
{
    class ShadowFrameBuffer
    {
        public:
        ShadowFrameBuffer();
        ShadowFrameBuffer(const uint32_t w, const uint32_t h);
        ShadowFrameBuffer(const ShadowFrameBuffer &rhs) = delete;

        bool Ready() const;
        uint32_t Width() const;
        uint32_t Height() const;
        const GLuint FramebufferHandle() const;
        const GLuint ShadowMapHandle() const;

        void Init();

        private:
        bool m_ready;
        uint32_t m_width;
        uint32_t m_height;
        GLuint m_shadowMap;
        GLuint m_frameBuffer;
    };
}

#endif
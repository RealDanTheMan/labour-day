#ifndef DEPTH_FRAME_BUFFER_HPP_
#define DEPTH_FRAME_BUFFER_HPP_

#include "gfx.hpp"

namespace Engine
{
    class DepthFramebuffer
    {
        public:
        DepthFramebuffer();
        DepthFramebuffer(const uint32_t w, const uint32_t h);
        DepthFramebuffer(const DepthFramebuffer &rhs) = delete;

        bool Ready() const;
        uint32_t Width() const;
        uint32_t Height() const;
        const GLuint FramebufferHandle() const;

        void Init();

        private:
        bool m_ready;
        uint32_t m_width;
        uint32_t m_height;
        GLuint m_depthMap;
        GLuint m_frameBuffer;
    };
}

#endif
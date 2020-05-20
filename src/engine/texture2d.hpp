#ifndef TEXTURE2D_HPP_
#define TEXTURE2D_HPP_

#include "gltex.hpp"
#include <memory>
#include <string>

namespace Engine
{
    class Texture2D
    {
        public:

        Texture2D();
        static std::unique_ptr<Texture2D> Load(const std::string &filepath);
        static bool Write(const Texture2D * const tex, const std::string &filepath);

        public:

        const uint32_t Width() const;
        const uint32_t Height() const;
        const uint32_t ChannelCount() const;
        unsigned char* const DataHandle() const;
        const GLuint GLHandle() const;
        void Free();
        bool Ready() const;
        bool GLReady() const;
        void GLPush();
        void GLPop();

        private:

        unsigned char *m_data;
        uint32_t m_width;
        uint32_t m_height;
        uint32_t m_channels;
        std::unique_ptr<GLTex> m_gltex;
    };
}

#endif
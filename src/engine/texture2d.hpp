#ifndef TEXTURE2D_HPP_
#define TEXTURE2D_HPP_

#include <memory>
#include <string>

namespace Engine
{
    class Texture2D
    {
        public:
        static std::unique_ptr<Texture2D> Load(const std::string &filepath);

        public:
        const uint32_t Width() const;
        const uint32_t Height() const;
        const uint32_t ChannelCount() const;
        unsigned char* const DataHandle() const;
        void Free();

        private:
        unsigned char *m_data;
        uint32_t m_width;
        uint32_t m_height;
        uint32_t m_channels;
    };
}

#endif
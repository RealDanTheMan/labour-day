#include "texture2d.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"
#include "debugging.hpp"
#include "sysutils.hpp"

using namespace Engine;


std::unique_ptr<Texture2D> Texture2D::Load(const std::string &filepath)
{
    assert (SysUtils::FileExists(filepath));

    int width;
    int height;
    int channels;

    unsigned char* rawdata = stbi_load(filepath.c_str(), &width, &height, &channels, 0);
    if(rawdata != nullptr)
    {
        std::unique_ptr<Texture2D> tex = std::make_unique<Texture2D>();
        tex->m_data = rawdata;
        tex->m_width = width;
        tex->m_height = height;
        tex->m_channels = channels;
        
        return tex;
    }
    
    return nullptr;
}

const uint32_t Texture2D::Width() const
{
    return m_width;
}

const uint32_t Texture2D::Height() const
{
    return m_height;
}

const uint32_t Texture2D::ChannelCount() const
{
    return m_channels;
}

unsigned char * const Texture2D::DataHandle() const
{
    return m_data;
}

void Texture2D::Free()
{
    if(m_data != nullptr)
    {
        stbi_image_free(m_data);
    }

    m_width = 0;
    m_height = 0;
    m_channels = 0;
}
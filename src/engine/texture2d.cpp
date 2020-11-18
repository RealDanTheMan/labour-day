#ifndef STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>
#endif

#ifndef STB_IMAGE_WRITE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb/stb_image_write.h>
#endif

#include "texture2d.hpp"
#include "debugging.hpp"
#include "sysutils.hpp"

using namespace Engine;

Texture2D::Texture2D():
m_gltex(std::make_unique<GLTex>()),
m_width(0),
m_height(0),
m_channels(0),
m_data(nullptr)
{
}

std::unique_ptr<Texture2D> Texture2D::Load(const std::string &filepath)
{
    assert (SysUtils::FileExists(filepath));
    //stbi_set_flip_vertically_on_load(true);

    int width;
    int height;
    int channels;

    unsigned char* rawdata = stbi_load(filepath.c_str(), &width, &height, &channels, STBI_rgb);
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

bool Texture2D::Write(const Texture2D * const tex, const std::string &filepath)
{
    assert (tex != nullptr);
    assert (tex->Ready());

    const int err = stbi_write_jpg(filepath.c_str(), tex->Width(), tex->Height(), tex->ChannelCount(), tex->DataHandle(), 100);
    return err;
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

const GLuint Texture2D::GLHandle() const
{
    assert (m_gltex != nullptr);
    return m_gltex->Handle();
}

bool Texture2D::Ready() const
{
    if(Width() == 0 || Height() == 0)
    {
        return false;
    }

    if(m_data == nullptr)
    {
        return false;
    }

    if(m_gltex == nullptr)
    {
        return false;
    }

    return true;
}

bool Texture2D::GLReady() const
{
    assert (m_gltex != nullptr);
    return m_gltex->Ready();
}

void Texture2D::Unload()
{
    if(m_gltex != nullptr && m_gltex->Ready())
    {
        m_gltex->Unload();
    }

    if(m_data != nullptr)
    {
        stbi_image_free(m_data);
        m_data = nullptr;
    }

    m_width = 0;
    m_height = 0;
    m_channels = 0;
    m_gltex = nullptr;
}

void Texture2D::GLPush()
{
    assert (m_gltex != nullptr);
    assert (m_data != nullptr);
    assert (Width() > 0 && Height() > 0);

    m_gltex->Load(Width(), Height(), m_data);
}

void Texture2D::GLPop()
{
    assert (m_gltex != nullptr);
    m_gltex->Unload();
}
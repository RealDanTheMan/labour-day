#include "gltex.hpp"
#include "debugging.hpp"

using namespace Engine;

GLTex::GLTex():
m_tex(0)
{
}

bool GLTex::Ready() const 
{
    if(m_tex == 0)
    {
        return false;
    }

    return true;
}

void GLTex::Load(const uint32_t w, const uint32_t h, unsigned char* const data)
{
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glGenTextures(1, &m_tex);
    glBindTexture(GL_TEXTURE_2D, m_tex);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 0);

    m_loaded = true;
}

void GLTex::Unload()
{
    glDeleteTextures(1, &m_tex);
    m_tex = 0;
    m_loaded = false;
}

const GLuint GLTex::Handle() const
{
    return m_tex;
}
#include "gltex.hpp"
#include "debugging.hpp"

using namespace Engine;

GLTex::GLTex(const Texture2D &tex):
m_tex(0)
{
    assert (tex.DataHandle() != nullptr);

    glGenTextures(1, &m_tex);
    glBindTexture(GL_TEXTURE_2D, m_tex);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, tex.Width(), tex.Height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, tex.DataHandle());
    glGenerateMipmap(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 0);
}

bool GLTex::Ready() const 
{
    if(m_tex == 0)
    {
        return false;
    }

    return true;
}

void GLTex::Free()
{
    glDeleteTextures(1, &m_tex);
    m_tex = 0;
}
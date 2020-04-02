#include "shaderprog.hpp"
#include "debugging.hpp"
#include <memory>

using namespace Engine;

ShaderProg::ShaderProg(const ShaderSource &vs, const ShaderSource &ps)
{
    assert (vs.GetType() == ShaderSource::ShaderSourceType::Vertex);
    assert (ps.GetType() == ShaderSource::ShaderSourceType::Pixel);

    m_handle = glCreateProgram();

    glAttachShader(m_handle, vs.GetHandle());
    glAttachShader(m_handle, ps.GetHandle());
    glBindFragDataLocation(m_handle, 0, SV_OUT_COLOR);
    glLinkProgram(m_handle);
    glDetachShader(m_handle, vs.GetHandle());
    glDetachShader(m_handle, ps.GetHandle());

    GLint status;
    glGetProgramiv(m_handle, GL_LINK_STATUS, &status);
    if(status == GL_TRUE)
    {
        m_ready = true;
    }
}

void ShaderProg::Free()
{
    assert (m_handle != 0);
    glDeleteProgram(m_handle);
    m_handle = 0;
    m_ready = false;

}

const bool ShaderProg::Ready() const
{
    return m_ready;
}

const GLuint ShaderProg::GetHandle() const
{
    return m_handle;
}

const std::string ShaderProg::GetLog() const
{
    if(m_handle == 0)
    {
        return "";
    }

    GLint len;
    glGetProgramiv(m_handle, GL_INFO_LOG_LENGTH, &len);

    char* log = new char[len];
    glGetProgramInfoLog(m_handle, len, &len, log); 

    std::string logstr = std::string(log, len);
    delete[] log;
    log = 0;

    return logstr;
}
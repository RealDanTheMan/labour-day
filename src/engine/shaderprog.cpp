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

const std::string ShaderProg::GetLog() const
{
    if(m_handle == 0)
    {
        return "";
    }

    GLint size;
    glGetProgramiv(m_handle, GL_INFO_LOG_LENGTH, &size);

    char* log = new char[size];
    GLint len;
    glGetProgramInfoLog(m_handle, size, &len, log); 

    std::string logstr = std::string(log, len);
    delete[] log;
    log = 0;

    return logstr;
}
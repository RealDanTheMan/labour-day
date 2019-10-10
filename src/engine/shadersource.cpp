#include "shadersource.hpp"
#include "debugging.hpp"
#include <string.h>

using namespace Engine;

ShaderSource::ShaderSource(const std::string &src, const ShaderSourceType &type):
m_source(src.c_str()),
m_len(src.length()),
m_handle(0),
m_type(type),
m_compiled(false)
{

}

void ShaderSource::Compile()
{
    assert(m_source != nullptr);
    assert (m_len > 0);
    assert (!m_compiled);
    assert (m_handle == 0);

    char* src = new char[m_len];
    strcpy(src, m_source);

    switch(m_type)
    {
        case ShaderSourceType::Vertex: m_handle = glCreateShader(GL_VERTEX_SHADER); break;
        case ShaderSourceType::Pixel: m_handle = glCreateShader(GL_FRAGMENT_SHADER); break;
    }

    assert (m_handle != 0);
    glShaderSourceARB(m_handle, 1, &m_source, &m_len);
    glCompileShader(m_handle);

    delete[] src;
    src = nullptr;

    GLint status;
    glGetObjectParameterivARB(m_handle, GL_COMPILE_STATUS, &status);
    if(status)
    {
        m_compiled = true;
    }
}

void ShaderSource::Free()
{
    glDeleteShader(m_handle);
    m_handle = 0;
    m_len = 0;
    delete[] m_source;
    m_source = nullptr;
    m_compiled = false;
}

const bool ShaderSource::Compiled() const
{
    return m_compiled;
}

const ShaderSource::ShaderSourceType ShaderSource::GetType() const
{
    return m_type;
}

const std::string ShaderSource::GetLog() const 
{
    assert (m_handle != 0);

    GLint len;
    glGetShaderiv(m_handle, GL_INFO_LOG_LENGTH, &len);
    if(len == 0)
    {
        return "";
    }

    GLchar* log = new GLchar[len];
    glGetInfoLogARB(m_handle, len, &len, log);
    std::string logstr = std::string(log);
    delete[] log;
    log = nullptr;
    return logstr;
}

const GLuint ShaderSource::GetHandle() const
{
    return m_handle;
}
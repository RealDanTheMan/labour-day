#include "shaderparam.hpp"

using namespace Engine;


ShaderParam::ShaderParam(const std::string &name):
m_name(name)
{

}

ShaderParam::ShaderParam(const ShaderParam &rhs):
m_name(rhs.m_name)
{

}

const std::string &ShaderParam::Name() const
{
    return m_name;
}

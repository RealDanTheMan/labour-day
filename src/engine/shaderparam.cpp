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

std::unique_ptr<ShaderParam> ShaderParam::Clone() const
{
    auto clone = std::make_unique<ShaderParam>(m_name);
    return clone;
}
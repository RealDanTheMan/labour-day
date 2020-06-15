#include "material.hpp"

using namespace Engine;

Material::Material(const ShaderProg &shader)
{
    assert (shader.Ready());
    assert (shader.ShaderParameters() != nullptr);

    m_params = ShaderParamCollection::Copy(*shader.ShaderParameters());
    m_shader = &shader;
}

ShaderParamCollection * const Material::ShaderParameters()
{
    return m_params.get();
}

const ShaderParamCollection * const Material::ShaderParameters() const
{
    return m_params.get();
}

const ShaderProg* Material::Shader() const
{
    assert (m_shader != nullptr);
    return m_shader;
}
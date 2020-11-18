#include "shaderparamcollection.hpp"
#include "debugging.hpp"
#include <algorithm>

using namespace Engine;

ShaderParamCollection::ShaderParamCollection()
{

}

std::unique_ptr<ShaderParamCollection> ShaderParamCollection::Create(const GLuint shader)
{
    assert (shader != 0);

    GLint linked = 0;
    glGetProgramiv(shader, GL_LINK_STATUS, &linked);
    assert (linked == GL_TRUE);

    auto params = std::make_unique<ShaderParamCollection>();

    // Fetch all shader uniform params
    GLuint texCount=0;
    GLint count;
    glGetProgramiv(shader, GL_ACTIVE_UNIFORMS, &count);
    for(uint32_t i=0; i < count; i++)
    {
        GLchar paramName[256];
        GLenum paramType;
        GLint paramSize;
        GLsizei paramLen;

        glGetActiveUniform(shader, (GLuint)i, (GLsizei)sizeof(paramName), &paramLen, &paramSize, &paramType, paramName);
        std::string name((char*)&paramName[0], paramLen);
        if(name.size() > 1 &&
            name[0] != 'S' && name[1] != 'V')
        {
            switch(paramType)
            {
                case GL_FLOAT: { params->AddParameter<float>(name); break; }
                case GL_FLOAT_VEC2: { params->AddParameter<Vec2>(name); break; }
                case GL_FLOAT_VEC3: { params->AddParameter<Vec3>(name); break; }
                case GL_FLOAT_VEC4: { params->AddParameter<Vec4>(name); break; }
                case GL_UNSIGNED_INT: { params->AddParameter<uint32_t>(name); break; }
                case GL_INT: { params->AddParameter<int>(name); break; }
                case GL_BOOL: { params->AddParameter<bool>(name); break; }
                case GL_FLOAT_MAT4: { params->AddParameter<Mat4>(name); break; }
                case GL_SAMPLER_2D:
                {
                    params->AddTexParameter(name, texCount);
                    texCount++;

                    break;
                }
            }
        }
    }

    return params;
}

std::unique_ptr<ShaderParamCollection> ShaderParamCollection::Copy(const ShaderParamCollection &rhs) 
{
    auto params = std::make_unique<ShaderParamCollection>();
    for(uint32_t i=0; i < rhs.Count(); i++)
    {
        params->m_params.push_back(rhs.m_params[i]->Clone());
        params->m_paramMap.insert(std::make_pair(
            params->m_params.back()->Name(),
            params->m_params.back().get()
        ));
    }

    for(uint32_t i=0; i < rhs.m_texParams.size(); i++)
    {
        params->m_texParams.push_back(rhs.m_texParams[i]);
    }

    return params;
}

const uint32_t ShaderParamCollection::Count() const
{
    return m_paramMap.size();
}

const std::vector<std::string> ShaderParamCollection::AllKeys() const
{
    std::vector<std::string> keys;
    for(auto it = m_paramMap.begin(); it != m_paramMap.end(); ++it) 
    {
        keys.push_back(it->first);
    }

    return keys;
}

const std::vector<std::string> ShaderParamCollection::TextureKeys() const
{
    std::vector<std::string> keys;
    for(auto it = m_paramMap.begin(); it != m_paramMap.end(); ++it) 
    {
        // Skip this param if its not tex param
        if(std::find(m_texParams.begin(), m_texParams.end(), it->first) == m_texParams.end())
        {
            continue;
        }

        const ShaderParamValue<TexVal>* paramv = reinterpret_cast<const ShaderParamValue<TexVal>*>(it->second);
        if(paramv != nullptr)
        {
            keys.push_back(it->first);
        }
    }

    return keys;
}

const TexVal ShaderParamCollection::GetTexValue(const std::string &name) const 
{
    assert (m_paramMap.find(name) != m_paramMap.end());
    const ShaderParam* const  param = m_paramMap.at(name);
    assert (param != nullptr);
    const ShaderParamValue<TexVal>* paramv = reinterpret_cast<const ShaderParamValue<TexVal>*>(param);
    assert (paramv != nullptr);

    return paramv->Get();
}

void ShaderParamCollection::SetTexValue(const std::string &name, Texture2D * const tex)
{
    assert (m_paramMap.find(name) != m_paramMap.end());
    ShaderParam* param = m_paramMap.at(name);
    assert (param != nullptr);
    ShaderParamValue<TexVal>* paramv = reinterpret_cast<ShaderParamValue<TexVal>*>(param);
    assert (paramv != nullptr);
    
    TexVal val = paramv->Get();
    val.m_tex = tex;
    paramv->Set(val);
}

void ShaderParamCollection::AddTexParameter(const std::string &name, GLuint idx)
{
    m_params.push_back(std::make_unique<ShaderParamValue<TexVal>>(name));
    m_paramMap.insert(std::make_pair(name, m_params.back().get()));
    m_texParams.push_back(name);
}
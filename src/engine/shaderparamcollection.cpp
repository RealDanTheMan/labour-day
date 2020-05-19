#include "shaderparamcollection.hpp"

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
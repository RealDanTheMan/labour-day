#include "material.hpp"

using namespace Engine;

Material::Material(const ShaderProg &shader)
{
    assert (shader.Ready());

    GLint linked = 0;
    glGetProgramiv(shader.GetHandle(), GL_LINK_STATUS, &linked);
    assert (linked == GL_TRUE);

    // Fetch all shader uniform params
    GLint count;
    glGetProgramiv(shader.GetHandle(), GL_ACTIVE_UNIFORMS, &count);
    for(uint32_t i=0; i < count; i++)
    {
        GLchar paramName[256];
        GLenum paramType;
        GLint paramSize;
        GLsizei paramLen;

        glGetActiveUniform(shader.GetHandle(), (GLuint)i, (GLsizei)sizeof(paramName), &paramLen, &paramSize, &paramType, paramName);
        std::string name((char*)&paramName[0], paramLen);
        if(name.size() > 1 &&
            name[0] != 'S' && name[1] != 'V')
        {
            switch(paramType)
            {
                case GL_FLOAT: { AddParameter<float>(name); break; }
                case GL_FLOAT_VEC2: { AddParameter<Vec2>(name); break; }
                case GL_FLOAT_VEC3: { AddParameter<Vec3>(name); break; }
                case GL_FLOAT_VEC4: { AddParameter<Vec4>(name); break; }
                case GL_UNSIGNED_INT: { AddParameter<uint32_t>(name); break; }
                case GL_INT: { AddParameter<int>(name); break; }
                case GL_BOOL: { AddParameter<bool>(name); break; }
                case GL_FLOAT_MAT4: { AddParameter<Mat4>(name); break; }
                case GL_SAMPLER_2D: { AddParameter<Texture2D*>(name); break; }
            }
        }
    }
}

const uint32_t Material::Count() const
{
    return m_paramMap.size();
}

const std::vector<std::string> Material::AllKeys() const
{
    std::vector<std::string> keys;
    for(auto it = m_paramMap.begin(); it != m_paramMap.end(); ++it) 
    {
        keys.push_back(it->first);
    }

    return keys;
}
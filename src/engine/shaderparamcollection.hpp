#ifndef SHADER_PARAM_COLLECTION_HPP_
#define SHADER_PARAM_COLLECTION_HPP_

#include "types.hpp"
#include "glewinterface.hpp"
#include "shaderparam.hpp"
#include "texture2d.hpp"
#include <memory>
#include <vector>
#include <map>

namespace Engine
{
    struct TexVal
    {
        Texture2D *m_tex;
        GLuint m_idx;

        TexVal():
        m_tex(nullptr),
        m_idx(0)
        {
        }

        TexVal(const TexVal &rhs):
        m_tex(rhs.m_tex),
        m_idx(rhs.m_idx)
        {
        }

        TexVal& operator=(TexVal other)
        {
            m_tex = other.m_tex;
            m_idx = other.m_idx;

            return *this;
        }
    };

    class ShaderParamCollection
    {
        public:
        ShaderParamCollection();
        ShaderParamCollection(const ShaderParamCollection &rhs) = delete;

        static std::unique_ptr<ShaderParamCollection> Create(const GLuint shaderHandle);
        static std::unique_ptr<ShaderParamCollection> Copy(const ShaderParamCollection &rhs);
        const uint32_t Count() const;
        const std::vector<std::string> AllKeys() const;
        const std::vector<std::string> TextureKeys() const;

        template <typename T>
        void SetValue(const std::string &name, const T &val);
        void SetTexValue(const std::string &name, Texture2D * const tex);
        template <typename T>
        const T GetValue(const std::string &name) const;
        const TexVal GetTexValue(const std::string &name) const;

        private:
        template <typename T>
        void AddParameter(const std::string &name);
        void AddTexParameter(const std::string &name, uint32_t idx);

        private :
        std::vector<std::unique_ptr<ShaderParam>> m_params;
        std::map<const std::string, ShaderParam*> m_paramMap;
    };

    template <typename T>
    void ShaderParamCollection::AddParameter(const std::string &name)
    {
        m_params.push_back(std::make_unique<ShaderParamValue<T>>(name));
        m_paramMap.insert(std::make_pair(name, m_params.back().get()));
    }

    template <typename T>
    const T ShaderParamCollection::GetValue(const std::string &name) const
    {
        assert (m_paramMap.find(name) != m_paramMap.end());

        const ShaderParam* const  param = m_paramMap.at(name);
        assert (param != nullptr);
        const ShaderParamValue<T>* paramv = reinterpret_cast<const ShaderParamValue<T>*>(param);
        assert (paramv != nullptr);
        return paramv->Get();
    }

    template <typename T>
    void ShaderParamCollection::SetValue(const std::string &name, const T &val)
    {
        assert (m_paramMap.find(name) != m_paramMap.end());

        ShaderParam* param = m_paramMap.at(name);
        assert (param != nullptr);
        ShaderParamValue<T>* paramv = reinterpret_cast<ShaderParamValue<T>*>(param);
        assert (paramv != nullptr);

        paramv->Set(val);
    }
}

#endif
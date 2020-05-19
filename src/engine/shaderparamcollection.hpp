#ifndef SHADER_PARAM_COLLECTION_HPP_
#define SHADER_PARAM_COLLECTION_HPP_

#include "types.hpp"
#include "glewinterface.hpp"
#include "shaderparam.hpp"
#include <memory>
#include <vector>
#include <map>

namespace Engine
{
    class ShaderParamCollection
    {
        public:
        ShaderParamCollection();
        ShaderParamCollection(const ShaderParamCollection &rhs) = delete;

        static std::unique_ptr<ShaderParamCollection> Create(const GLuint shaderHandle);
        static std::unique_ptr<ShaderParamCollection> Copy(const ShaderParamCollection &rhs);
        const uint32_t Count() const;
        const std::vector<std::string> AllKeys() const;

        template <typename T>
        void SetValue(const std::string &name, const T &val);
        template <typename T>
        const T GetValue(const std::string &name) const;

        private:
        template <typename T>
        void AddParameter(const std::string &name);

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
#ifndef MATERIAL_HPP_
#define MATERIAL_HPP_

#include "shaderprog.hpp"
#include "shaderparam.hpp"
#include "types.hpp"
#include "texture2d.hpp"
#include <map>
#include <vector>
#include "debugging.hpp"

namespace Engine
{
    class Material
    {
        public:
        Material(const ShaderProg &shader);
        Material(const Material &rhs) = delete;

        public:
        const uint32_t Count() const;
        const std::vector<std::string> AllKeys() const;

        template <typename T>
        void SetValue(const std::string &name, const T &val);
        template <typename T>
        const T GetValue(const std::string &name) const;

        private:
        template <typename T>
        void AddParameter(const std::string &name);

        private:
        std::map<const std::string, std::unique_ptr<ShaderParam>> m_paramMap;
    };

    template <typename T>
    void Material::AddParameter(const std::string &name)
    {
        m_paramMap[name] = std::make_unique<ShaderParamValue<T>>(name);
    }

    template <typename T>
    const T Material::GetValue(const std::string &name) const
    {
        assert (m_paramMap.find(name) != m_paramMap.end());

        const ShaderParam* const  param = m_paramMap.at(name).get();
        assert (param != nullptr);
        const ShaderParamValue<T>* paramv = reinterpret_cast<const ShaderParamValue<T>*>(param);
        assert (paramv != nullptr);
        return paramv->Get();
    }

    template <typename T>
    void Material::SetValue(const std::string &name, const T &val)
    {
        assert (m_paramMap.find(name) != m_paramMap.end());

        ShaderParam* param = m_paramMap.at(name).get();
        assert (param != nullptr);
        ShaderParamValue<T>* paramv = reinterpret_cast<ShaderParamValue<T>*>(param);
        assert (paramv != nullptr);

        paramv->Set(val);
    }
}

#endif
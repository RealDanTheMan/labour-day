#ifndef SHADER_PARAM_HPP_
#define SHADER_PARAM_HPP_

#include "string"
#include "types.hpp"

namespace Engine
{
    class ShaderParam
    {
        public:
        ShaderParam(const std::string &name);
        ShaderParam(const ShaderParam &rhs);
        const std::string &Name() const;

        virtual std::unique_ptr<ShaderParam> Clone() const;

        protected:
        std::string m_name;
    };

    template <class T>
    class ShaderParamValue : public ShaderParam
    {
        private:
        T m_value;

        public:
        ShaderParamValue<T>(const std::string &name, T val);
        ShaderParamValue<T>(const std::string &name);
        const T Get() const;
        void Set(T val);
        virtual std::unique_ptr<ShaderParam> Clone() const override;
    };

    template <class T>
    ShaderParamValue<T>::ShaderParamValue(const std::string &name, T val) : ShaderParam(name), m_value(val)
    {
    }

    template <class T>
    ShaderParamValue<T>::ShaderParamValue(const std::string &name) : ShaderParam(name)
    {
    }

    template <class T>
    const T ShaderParamValue<T>::Get() const
    {
        return m_value;
    }

    template <class T>
    void ShaderParamValue<T>::Set(T val)
    {
        m_value = val;
    }

    template<class T>
    std::unique_ptr<ShaderParam> ShaderParamValue<T>::Clone() const
    {
        auto clone = std::make_unique<ShaderParamValue<T>>(m_name);
        return clone;
    }
}

#endif
#ifndef RESOURCE_CACHE_HPP_
#define RESOURCE_CACHE_HPP_

#include "types.hpp"
#include "iresource.hpp"
#include <vector>
#include <string>

namespace Engine
{
    class ResourceCache
    {
        public:
        ResourceCache() = default;
        ResourceCache(const ResourceCache &rhs) = delete;

        virtual void Free();
        uint32_t Count() const;

        protected:
        template <typename T>
        void Consume(T *pdata, const std::string &key);
        bool HasResourceKey(const std::string &key) const;
        uint32_t ResourceIdx(const std::string &key) const;
        IResource * const GetResource(const std::string &key) const;

        private:
        std::vector<std::unique_ptr<IResource>> m_resources;
        std::vector<std::string> m_keys;
    };

    template <typename T>
    void ResourceCache::Consume(T *pdata, const std::string &key)
    {
        static_assert (std::is_base_of<IResource, T>::value, "Invalid template type, expected derived from <IResource>");
        assert (HasResourceKey(key) == false);

        assert (pdata != nullptr);
        assert (key.size() > 0);

        m_keys.push_back(key);
        m_resources.push_back(std::unique_ptr<T>(pdata));
    }
}

#endif
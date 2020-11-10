#ifndef ASSET_CACHE_HPP_
#define ASSET_CACHE_HPP

#include "texture2d.hpp"
#include "contentserialiser.hpp"
#include <vector>
#include <memory>
#include <string>

namespace Engine
{
    class AssetCache
    {
        public:
        AssetCache();
        AssetCache(const AssetCache& rhs) = delete;

        uint32_t Count() const;
        bool AddTexture(const std::string &filepath, const std::string &key);
        bool AddMesh(const std::string &filepath, const std::string &key);
        bool AddModel(const std::string &filepath, const std::string &key);
        bool AddPrefab(const std::string &filepath, const std::string &key);
        void Free();

        Texture2D * const GetTexture(const std::string &key) const;
        Mesh * const GetMesh(const std::string &key) const;
        Prefab * const GetPrefab(const std::string &key) const;

        private:
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
    void AssetCache::Consume(T *pdata, const std::string &key)
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
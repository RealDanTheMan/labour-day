#ifndef ASSET_CACHE_HPP_
#define ASSET_CACHE_HPP

#include "texture2d.hpp"
#include "resourcecache.hpp"
#include "contentserialiser.hpp"
#include "entityserialiser.hpp"
#include "runtimeshaders.hpp"
#include <vector>
#include <memory>
#include <string>

namespace Engine
{
    class AssetCache : public ResourceCache
    {
        public:
        AssetCache();
        AssetCache(const AssetCache& rhs) = delete;

        bool AddTexture(const std::string &filepath, const std::string &key);
        bool AddMesh(const std::string &filepath, const std::string &key);
        bool AddMaterial(const std::string &filepath, const std::string &key);
        bool AddModel(const std::string &filepath, const std::string &key);
        bool AddPrefab(const std::string &filepath, const std::string &key);
        bool AddFromManifest(const std::string &filepath);

        virtual void Free() override;

        Texture2D * const GetTexture(const std::string &key) const;
        Mesh * const GetMesh(const std::string &key) const;
        Material * const GetMaterial(const std::string &key) const;
        Model * const GetModel(const std::string &key) const;
        Prefab * const GetPrefab(const std::string &key) const;

        private:
        std::unique_ptr<RuntimeShaders> m_rtShaders;
    };

    
}

#endif
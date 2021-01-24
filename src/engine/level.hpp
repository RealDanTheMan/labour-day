#ifndef LEVEL_HPP_
#define LEVEL_HPP_

#include "assetcache.hpp"
#include "ecssys.hpp"

namespace Engine
{
    class Level
    {
        public:
        Level(const AssetCache * pAssetCache, ECSSys *pEcs);
        Level(const Level &rhs) = delete;

        void AddObjectsFromManifest(const std::string &filepath);
        std::vector<Entity*> GetEntitiesByTag(const std::string &tag);

        private:
        std::vector<Entity*> m_entities;
        const AssetCache * m_cache;
        ECSSys * m_ecs;
    };
}

#endif
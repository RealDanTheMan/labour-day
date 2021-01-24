#include "level.hpp"
#include "components/transformcomponent.hpp"
#include "contentserialiser.hpp"

using namespace Engine;

Level::Level(const AssetCache *pAssetCache, ECSSys *pEcs):
m_cache(pAssetCache),
m_ecs(pEcs)
{

}

void Level::AddObjectsFromManifest(const std::string &filepath)
{
    assert (m_cache != nullptr);
    assert (m_ecs != nullptr);
    assert (filepath.size() > 0);

    D_MSG ("Loading level object ...");

    std::unique_ptr<ContentLevelInfo> pInfo = ContentSerialiser::LoadLevelInfo(filepath);
    assert (pInfo != nullptr);

    for(auto &obj : pInfo->m_objects)
    {
        // Validate this sceen object resource refs are valid
        assert (obj->m_id.size() > 0);
        assert (m_cache->HasResourceKey(obj->m_id));

        // Get prefab handle of this object from resource cache
        Prefab *pPrefab = m_cache->GetPrefab(obj->m_id);
        assert (pPrefab != nullptr);

        // Instantianate entity from prefab
        Entity * pEntity = m_ecs->CreateEntity(pPrefab);
        m_entities.push_back(pEntity);

        // Update this object position if it has transform component
        if(pEntity->GetTransform() != nullptr)
        {
            const Vec3 pos = SerialisationUtils::Vec3FromString(obj->m_pos);
            pEntity->GetTransform()->GetTransform().SetTranslation(pos);
        }
    }
}
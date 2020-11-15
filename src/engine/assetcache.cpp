#include "assetcache.hpp"
#include "meshgen.hpp"

#include <algorithm>

using namespace Engine;

AssetCache::AssetCache()
{
    m_rtShaders = std::make_unique<RuntimeShaders>();
    m_rtShaders->Init();
}

void AssetCache::Free()
{
    for(uint32_t i=0; i < m_resources.size(); i++)
    {
        assert (m_resources[i] != nullptr);

        m_resources[i]->Unload();
        m_resources[i].reset(nullptr);
    }

    m_resources.clear();
    m_keys.clear();
    m_rtShaders->Free();
}

bool AssetCache::AddTexture(const std::string &filepath, const std::string &key)
{
    auto tex = Texture2D::Load(filepath);
    if(tex != nullptr)
    {
        Texture2D *pdata = tex.get();
        tex.release();

        Consume<Texture2D>(pdata, key);
        return true;
    }

    return false;
}

bool AssetCache::AddMesh(const std::string &filepath, const std::string &key)
{
    auto msh = ContentSerialiser::LoadMesh(filepath);
    if(msh != nullptr)
    {
        Mesh *pdata = msh.get();
        msh.release();

        Consume<Mesh>(pdata, key);
        return true;
    }

    return false;
}

bool AssetCache::AddMaterial(const std::string &filepath, const std::string &key)
{
    assert (m_rtShaders->Ready());

    std::unique_ptr<ContentMaterialInfo> matInfo = ContentSerialiser::LoadMaterialInfo(filepath);
    if(matInfo != nullptr)
    {
        // For now we only support built in shaders
        const ShaderProg* shader = m_rtShaders->GetByName(matInfo->m_shaderKey);
        assert (shader != nullptr);

        std::unique_ptr<Material> mat = std::make_unique<Material>(*shader);
        Material *pData = mat.get();
        mat.release();

        Consume<Material>(pData, key);
        return true;
    }

    return false;
}

bool AssetCache::AddModel(const std::string &filepath, const std::string &key)
{
    auto modelInfo = ContentSerialiser::LoadModelInfo(filepath);
    if(modelInfo != nullptr)
    {
        assert (HasResourceKey(modelInfo->m_materialKey));
        assert (HasResourceKey(modelInfo->m_meshKey));

        Mesh *pMesh = GetMesh(modelInfo->m_meshKey);
        Material *pMat = GetMaterial(modelInfo->m_materialKey);

        std::unique_ptr<Model> model = std::make_unique<Model>(*pMesh, pMat);
        Model *pData = model.get();
        model.release();

        Consume<Model>(pData, key);
        return true;
    }

    return false;
}

bool AssetCache::AddPrefab(const std::string &filepath, const std::string &key)
{
    auto prf = ContentSerialiser::LoadPrefab(filepath);
    if(prf != nullptr)
    {
        Prefab * pdata = prf.get();
        prf.release();

        Consume<Prefab>(pdata, key);
        return true;
    }

    return false;
}

bool AssetCache::HasResourceKey(const std::string &key) const
{
    if(std::find(m_keys.begin(), m_keys.end(), key) != m_keys.end())
    {
        return true;
    }

    return false;
}

uint32_t AssetCache::ResourceIdx(const std::string &key) const
{
    assert (HasResourceKey(key));

    std::vector<std::string>::const_iterator it = std::find(m_keys.begin(), m_keys.end(), key);
    return std::distance(m_keys.begin(), it);
}

uint32_t AssetCache::Count() const
{
    return m_resources.size();
}

IResource * const AssetCache::GetResource(const std::string &key) const
{
    if(HasResourceKey(key))
    {
        const uint32_t idx = ResourceIdx(key);
        return m_resources[idx].get();
    }

    return nullptr;
}

Texture2D * const AssetCache::GetTexture(const std::string &key) const
{
    IResource * const pres = GetResource(key);
    if(pres != nullptr)
    {
        Texture2D * const ptex = dynamic_cast<Texture2D *>(pres);
        assert(ptex != nullptr);

        return ptex;
    }

    return nullptr;
}

Mesh * const AssetCache::GetMesh(const std::string &key) const
{
    IResource * const pres = GetResource(key);
    if(pres != nullptr)
    {
        Mesh * const pmsh = dynamic_cast<Mesh*>(pres);
        assert (pmsh != nullptr);

        return pmsh;
    }

    return nullptr;
}

Material * const AssetCache::GetMaterial(const std::string &key) const
{
    IResource * const pRes = GetResource(key);
    if(pRes != nullptr)
    {
        Material * const pMat = dynamic_cast<Material*>(pRes);
        assert (pMat != nullptr);

        return pMat;
    }

    return nullptr;
}

Model * const AssetCache::GetModel(const std::string &key) const
{
    IResource * const pRes = GetResource(key);
    if(pRes != nullptr)
    {
        Model * const pModel = dynamic_cast<Model*>(pRes);
        assert (pModel != nullptr);

        return pModel;
    }

    return nullptr;
}

Prefab * const AssetCache::GetPrefab(const std::string &key) const
{
    IResource * const pres = GetResource(key);
    if(pres != nullptr)
    {
        Prefab * const pPrefab = dynamic_cast<Prefab*>(pres);
        assert (pPrefab != nullptr);

        return pPrefab;
    }
    
    return nullptr;
}
#include "assetcache.hpp"
#include "meshgen.hpp"
#include "components/modelcomponent.hpp"

using namespace Engine;

AssetCache::AssetCache()
{
    m_rtShaders = std::make_unique<RuntimeShaders>();
    m_rtShaders->Init();
}

void AssetCache::Free()
{
    ResourceCache::Free();
    
    if(m_rtShaders != nullptr)
    {
        m_rtShaders->Free();
    }
}

bool AssetCache::AddTexture(const std::string &filepath, const std::string &key)
{
    D_MSG("Loading texture asset -> " + key);
    auto tex = Texture2D::Load(filepath);

    if(tex != nullptr)
    {
        Texture2D *pdata = tex.get();
        tex.release();

        Consume<Texture2D>(pdata, key);
        GetTexture(key)->GLPush();
        
        return true;
    }

    return false;
}

bool AssetCache::AddMesh(const std::string &filepath, const std::string &key)
{
    D_MSG("Loading mesh asset -> " + key);
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
    D_MSG("Loading material asset -> " + key);
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

        // TODO: Push shader param values
        for (auto &param : matInfo->m_params)
        {
            SerialisationUtils::ValueType paramType = SerialisationUtils::GetTypeFromTypeString(param->m_type);
            if(paramType == SerialisationUtils::ValueType::Texture2D)
            {
                // Texture parameters
                Texture2D * tex = GetTexture(param->m_value);
                assert (tex != nullptr);

                pData->ShaderParameters()->SetTexValue(param->m_name, tex);
            }
            else 
            {
                switch (paramType)
                {
                    case SerialisationUtils::ValueType::Int:
                    {
                        int val = SerialisationUtils::IntFromString(param->m_value);
                        pData->ShaderParameters()->SetValue(param->m_name, val);
                        break;
                    }
                    case SerialisationUtils::ValueType::Float:
                    {
                        float val = SerialisationUtils::FloatFromString(param->m_value);
                        pData->ShaderParameters()->SetValue(param->m_name, val);
                        break;
                    }
                    case SerialisationUtils::ValueType::Vector2:
                    {
                        Vec2 val = SerialisationUtils::Vec2FromString(param->m_value);
                        pData->ShaderParameters()->SetValue(param->m_name, val);
                        break;
                    }
                    case SerialisationUtils::ValueType::Vector3:
                    {
                        Vec3 val = SerialisationUtils::Vec3FromString(param->m_value);
                        pData->ShaderParameters()->SetValue(param->m_name, val);
                        break;
                    }
                    case SerialisationUtils::ValueType::Vector4:
                    {
                        Vec4 val = SerialisationUtils::Vec4FromString(param->m_value);
                        pData->ShaderParameters()->SetValue(param->m_name, val);
                        break;
                    }
                    default:
                    {
                        throw std::runtime_error("Value type handling not yet implemented !");
                        break;
                    }
                }
            }
        }

        Consume<Material>(pData, key);
        return true;
    }

    return false;
}

bool AssetCache::AddModel(const std::string &filepath, const std::string &key)
{
    D_MSG("Loading model asset -> " + key);
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
    D_MSG("Loading prefab asset -> " + key);
    auto entityInfo = ContentSerialiser::LoadEntityInfo(filepath);

    if(entityInfo != nullptr)
    {
        // Entities are a bit more complex to deserialise so we invoke bespoke implementation
        std::vector<std::unique_ptr<Entity>> entities = EntitySerialiser::Deserialise(entityInfo.get(), this);

        // Create prefab & consume it
        auto prefab = std::make_unique<Prefab>(entities);
        Prefab *pData = prefab.get();
        prefab.release();

        Consume<Prefab>(pData, key);
        return true;
    }

    return false;
}

bool AssetCache::AddFromManifest(const std::string &filepath)
{
    assert (filepath.size() > 0);
    D_MSG ("Loading asset resouces from cache ...");

    std::unique_ptr<ContentManifestInfo> manifestInfo = ContentSerialiser::LoadManifestInfo(filepath);
    //manifestInfo->Printout();
    
    if(manifestInfo != nullptr)
    {
        for(auto it = manifestInfo->m_textures.begin(); it !=  manifestInfo->m_textures.end(); ++it) 
        {
            //D_MSG ("RES: " + it->second + " : " + it->first);
            AddTexture(it->second, it->first);
        }

        for(auto it = manifestInfo->m_meshes.begin(); it !=  manifestInfo->m_meshes.end(); ++it) 
        {
            //D_MSG ("RES: " + it->second + " : " + it->first);
            AddMesh(it->second, it->first);
        }
        
        for(auto it = manifestInfo->m_materials.begin(); it !=  manifestInfo->m_materials.end(); ++it) 
        {
            //D_MSG ("RES: " + it->second + " : " + it->first);
            AddMaterial(it->second, it->first);
        }

        for(auto it = manifestInfo->m_models.begin(); it !=  manifestInfo->m_models.end(); ++it) 
        {
            //D_MSG ("RES: " + it->second + " : " + it->first);
            AddModel(it->second, it->first);
        }

        for(auto it = manifestInfo->m_prefabs.begin(); it !=  manifestInfo->m_prefabs.end(); ++it) 
        {
            //D_MSG ("RES: " + it->second + " : " + it->first);
            AddPrefab(it->second, it->first);
        }

        D_MSG ("Cache loaded from manifest successfully !");
        return true;
    }

    D_MSG ("Failed to load asset resources from manifest !");
    return false;
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
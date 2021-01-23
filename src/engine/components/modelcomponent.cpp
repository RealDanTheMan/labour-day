#include "modelcomponent.hpp"

using namespace Engine::Components;

ModelComponentSerialiser::ModelComponentSerialiser() : EntityComponentSerialiser("ModelComponentClass")
{
}

ModelComponentSerialiser::~ModelComponentSerialiser()
{
}

bool ModelComponentSerialiser::Deserialise(
    EntityComponent* pComponent, 
    const ContentEntityComponentInfo * pComponentInfo,
    const ResourceCache *pResourceCache) const
{
    assert (pComponent != nullptr);

    auto pCom = reinterpret_cast<ModelComponent*>(pComponent);
    assert (pCom != nullptr);

    bool isGood = false;
    for (uint32_t i=0; i < pComponentInfo->m_properties.size(); i++)
    {
        const ContentPropertyInfo * pProperty = pComponentInfo->m_properties[i].get();
        if(pProperty->m_name == "model")
        {
            // Validate resource cache state
            assert (pResourceCache != nullptr);
            assert (pResourceCache->HasResourceKey(pProperty->m_value));
            
            // Find model resource this component is expecting
            auto pRes = pResourceCache->GetResource(pProperty->m_value);
            Model *pModel = dynamic_cast<Model*>(pRes);
            assert (pModel != nullptr);

            // Update model resource on this component
            pCom->SetModel(pModel);
            isGood = true;
        }
    }

    if(isGood)
    {
        return true;
    }

    return false;
}

bool ModelComponentSerialiser::DeserialiseAdd(
    Entity* pEntity, 
    const ContentEntityComponentInfo * pComponentInfo,
    const ResourceCache *pResourceCache) const
{
    assert (pEntity != nullptr);
    assert (pComponentInfo != nullptr);
    auto pCmp = pEntity->Components().Add<ModelComponent>();
    assert (pCmp != nullptr);

    bool stat = Deserialise(pCmp, pComponentInfo, pResourceCache);
    if(stat)
    {
        return true;
    }

    return false;
}

ModelComponent::ModelComponent(): TransformComponent(),
    m_modelInstance(nullptr)
{
}

ModelComponent::ModelComponent(const ModelComponent &rhs): TransformComponent(rhs),
    m_modelInstance(std::make_unique<ModelInstance>(*rhs.m_modelInstance)),
    m_modelName(rhs.m_modelName)
{
}

ModelComponent::~ModelComponent()
{
}

void ModelComponent::SetModel(Model * model)
{
    m_modelInstance = std::make_unique<ModelInstance>(model);
}

void ModelComponent::SetModelRefName(const std::string &name)
{
    m_modelName = name;
}

const Engine::ModelInstance * ModelComponent::GetModelInstance() const
{
    return m_modelInstance.get();
}

Engine::ModelInstance * ModelComponent::GetModelInstance()
{
    return m_modelInstance.get();
}

const Engine::Model * ModelComponent::GetModel() const
{
    assert (m_modelInstance != nullptr);
    return m_modelInstance->GetModel();
}

const std::string & ModelComponent::GetModelRefName() const
{
    return m_modelName;
}

const bool ModelComponent::InternalModelRefOnly() const
{
    return false;
}

void ModelComponent::Init()
{

}

std::unique_ptr<Engine::EntityComponent> ModelComponent::Duplicate() const
{
    return std::make_unique<ModelComponent>(*this);
}

void ModelComponent::OnTransformChanged(const Transform &tr)
{
    // Propagate component transform to the model instance
    if(m_modelInstance != nullptr)
    {
        m_modelInstance->GetTransform().Set(tr);
    }
}
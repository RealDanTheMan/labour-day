#include "modelcomponent.hpp"

using namespace Engine::Components;

ModelComponentSerialiser::ModelComponentSerialiser() : EntityComponentSerialiser("ModelComponentClass")
{
}

ModelComponentSerialiser::~ModelComponentSerialiser()
{
}

bool ModelComponentSerialiser::Deserialise(EntityComponent* pComponent, const ContentEntityComponentInfo * pComponentInfo) const
{
    assert (pComponent != nullptr);

    auto pCmp = reinterpret_cast<ModelComponent*>(pComponent);
    assert (pCmp != nullptr);

    bool isGood = false;

    // Make sure model component contains actual reference to a model
    // No the best to be honest but it will do for now
    for (uint32_t i=0; i < pComponentInfo->m_properties.size(); i++)
    {
        const ContentPropertyInfo * property = pComponentInfo->m_properties[i].get();
        if(property->m_name == "model")
        {
            pCmp->m_modelName = property->m_value;
            isGood = true;
        }
    }

    if(isGood)
    {
        return true;
    }

    return false;
}

bool ModelComponentSerialiser::DeserialiseAdd(Entity* pEntity, const ContentEntityComponentInfo * pComponentInfo) const
{
    assert (pEntity != nullptr);
    assert (pComponentInfo != nullptr);
    auto pCmp = pEntity->Components().Add<ModelComponent>();
    assert (pCmp != nullptr);

    bool stat = Deserialise(pCmp, pComponentInfo);
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
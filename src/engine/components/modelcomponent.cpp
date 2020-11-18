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

ModelComponent::ModelComponent():
    m_model(nullptr)
{
}

ModelComponent::ModelComponent(const ModelComponent &rhs):
    m_model(rhs.m_model)
{
}

ModelComponent::~ModelComponent()
{
}

void ModelComponent::SetModel(Model * const model)
{
    m_model = model;
}

Engine::Model* const ModelComponent::ModelHandle() const
{
    return m_model;
}

Engine::Renderable * const ModelComponent::GetRenderable() const 
{
    if(m_model == nullptr)
    {
        return nullptr;
    }

    assert (m_model->GetRenderable()->Ready());
    return m_model->GetRenderable();
}

void ModelComponent::Init()
{
    if(!m_modelName.empty())
    {
        
    }
}

std::unique_ptr<Engine::EntityComponent> ModelComponent::Duplicate() const
{
    auto dup = std::make_unique<ModelComponent>();
    dup->m_modelName = m_modelName;

    if(m_model != nullptr)
    {
        dup->SetModel(m_model);
    }

    return dup;
}
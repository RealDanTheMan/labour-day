#include "modelcomponent.hpp"

using namespace Engine::Components;

ModelComponentSerialiser::ModelComponentSerialiser() : EntityComponentSerialiser("ModelComponentClass")
{
}

ModelComponentSerialiser::~ModelComponentSerialiser()
{
}

bool ModelComponentSerialiser::Deserialise(EntityComponent* pComponent, const configuru::Config &json) const
{
    assert (pComponent != nullptr);

    auto pCmp = reinterpret_cast<ModelComponent*>(pComponent);
    assert (pCmp != nullptr);

    if(json.has_key("modelname") && json["modelname"].is_string())
    {
        pCmp->m_modelName = (std::string)json["modelname"];
    }
    else 
    {
        return false;
    }

    return true;
}

bool ModelComponentSerialiser::DeserialiseAdd(Entity* pEntity, const configuru::Config &json) const
{
    assert (pEntity != nullptr);
    auto pCmp = pEntity->Components().Add<ModelComponent>();
    assert (pCmp != nullptr);

    bool stat = Deserialise(pCmp, json);
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

    assert (m_model->GetRenderable().Ready());
    return &(m_model->GetRenderable());
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
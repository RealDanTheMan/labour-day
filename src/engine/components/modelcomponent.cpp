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
    return false;
}

bool ModelComponentSerialiser::DeserialiseAdd(Entity* pEntity, const configuru::Config &json) const
{
    return false;
}

ModelComponentSerialiser ModelComponent::m_serialiser = ModelCompo;

ModelComponent::ModelComponent():
    m_model(nullptr)
{
}

ModelComponent::ModelComponent(const ModelComponent &rhs):
    m_model(rhs.m_model)
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
    
}

Engine::EntityComponentSerialiser * const ModelComponent::Seriaialiser()
{
    return &m_serialiser;
}
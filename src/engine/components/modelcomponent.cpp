#include "modelcomponent.hpp"

using namespace Engine::Components;

Engine::EntityComponentDesc ModelComponent::m_desc = {
    1,
    "ModelComponentClass"
};


ModelComponent::ModelComponent():
    m_model(nullptr)
{
    Engine::EntityComponentFac::RegieterClass(Engine::EntityComponentDesc());
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

const Engine::EntityComponentDesc &ModelComponent::StaticDesc()
{
    return ModelComponent::m_desc;
}

const Engine::EntityComponentDesc& ModelComponent::Desc()
{
    return ModelComponent::StaticDesc();    
}
#include "modelcomponent.hpp"

using namespace Engine::Components;


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
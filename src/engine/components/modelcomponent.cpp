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

void ModelComponent::SetModel(const Model *model)
{
    m_model = m_model;
}

const Engine::Model* const ModelComponent::ModelHandle() const
{
    return m_model;
}
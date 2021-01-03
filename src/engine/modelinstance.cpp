#include "modelinstance.hpp"

using namespace Engine;

ModelInstance::ModelInstance(Model * model):
m_model(model),
m_tr()
{
    assert (model != nullptr);
}

const Model * const ModelInstance::GetModel() const
{
    return m_model;
}

Transform & ModelInstance::GetTransform()
{
    return m_tr;
}

const Transform & ModelInstance::GetTransform() const
{
    return m_tr;
}
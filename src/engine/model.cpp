#include "model.hpp"


using namespace Engine;


Model::Model(Renderable& renderable):
    m_renderable(renderable),
    m_tr(Transform())
{

}

Model::Model(const Model& rhs):
    m_renderable(rhs.m_renderable),
    m_tr(rhs.m_tr)
{

}

Renderable& Model::GetRenderable()
{
    return m_renderable;
}

Transform& Model::GetTransform()
{
    return m_tr;
}
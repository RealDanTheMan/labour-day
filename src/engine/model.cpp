#include "model.hpp"

using namespace Engine;


Model::Model(Renderable& renderable, Material * const mat):
    m_renderable(renderable),
    m_tr(Transform()),
    m_mat(mat)
{

}

Model::Model(const Model& rhs):
    m_renderable(rhs.m_renderable),
    m_tr(rhs.m_tr),
    m_mat(rhs.m_mat)
{

}

Renderable &Model::GetRenderable()
{
    return m_renderable;
}

Transform &Model::GetTransform()
{
    return m_tr;
}

Material * const Model::GetMaterial() const
{
    return m_mat;
}
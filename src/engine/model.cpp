#include "model.hpp"

using namespace Engine;


Model::Model(const Mesh& mesh, Material * const mat):
    m_renderable(nullptr),
    m_tr(Transform()),
    m_mat(mat)
{
    m_renderable = std::make_unique<Renderable>();
    m_renderable->Init(mesh);
    m_renderable->BindShader(mat->Shader());

    assert (m_renderable->Ready());
}

const Renderable *Model::GetRenderable() const
{
    return m_renderable.get();
}

Transform &Model::GetTransform()
{
    return m_tr;
}

const Transform & Model::GetTransform() const
{
    return m_tr;
}

Material * const Model::GetMaterial() const
{
    return m_mat;
}

void Model::Unload()
{
    m_renderable->Free();
    m_renderable.reset(nullptr);
}
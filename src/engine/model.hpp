#ifndef MODEL_HPP_
#define MODEL_HPP_

#include "renderable.hpp"
#include "transform.hpp"
#include "material.hpp"

namespace Engine
{
    class Model : public IResource
    {
        public:
        Model(const Mesh& mesh, Material * const mat);
        Model(const Model& rhs)=delete;

        const Renderable* GetRenderable() const;
        Transform& GetTransform();
        const Transform & GetTransform() const;
        Material* const GetMaterial() const;
        virtual void Unload() override;

        private:
        std::unique_ptr<Renderable> m_renderable;
        Transform m_tr;
        Material* m_mat;
    };
}

#endif
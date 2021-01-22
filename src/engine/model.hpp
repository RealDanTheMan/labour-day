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

    class IModelRef
    {
        public:
        IModelRef() = default;
        IModelRef(const IModelRef &rhs) = default;
        
        virtual void SetModel(Model *pModel) =0;
        virtual void SetModelRefName(const std::string &name) =0;
        virtual const Model * GetModel() const =0;
        virtual const std::string & GetModelRefName() const =0;
        virtual const bool InternalModelRefOnly() const =0;
    };
}

#endif
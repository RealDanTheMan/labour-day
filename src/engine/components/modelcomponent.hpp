#ifndef MODEL_COMPONENT_HPP_
#define MODEL_COMPONENT_HPP_


#include "../entity.hpp"
#include "../model.hpp"
#include "../renderable.hpp"

namespace Engine::Components
{
    class ModelComponent: public EntityComponent
    {
        public:
        ModelComponent();
        ModelComponent(const ModelComponent &rhs);

        virtual void Init() override;
        virtual const EntityComponentDesc& Desc() override;

        void SetModel(Model * const model);
        Model* const ModelHandle() const;
        Renderable* const GetRenderable() const;

        public:
        static const EntityComponentDesc& StaticDesc();

        private:
        Model *m_model;
        static EntityComponentDesc m_desc;
    };
}

#endif
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

        void SetModel(Model * const model);
        Model* const ModelHandle() const;
        Renderable* const GetRenderable() const;

        private:
        Model *m_model;
    };
}

#endif
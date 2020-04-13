#ifndef MODEL_COMPONENT_HPP_
#define MODEL_COMPONENT_HPP_


#include "../entity.hpp"
#include "../model.hpp"

namespace Engine::Components
{
    class ModelComponent: public EntityComponent
    {
        public:
        ModelComponent();
        ModelComponent(const ModelComponent &rhs);

        void SetModel(const Model *model);
        const Model* const ModelHandle() const;

        private:
        Model *m_model;
    };
}

#endif
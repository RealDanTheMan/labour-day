#ifndef MODEL_COMPONENT_HPP_
#define MODEL_COMPONENT_HPP_


#include "../entity.hpp"
#include "../entityserialiser.hpp"
#include "../model.hpp"
#include "../renderable.hpp"

namespace Engine::Components
{
    class ModelComponentSerialiser : public EntityComponentSerialiser
    {
        public:
        ModelComponentSerialiser();
        virtual ~ModelComponentSerialiser();
        bool Deserialise(EntityComponent* pComponent, const configuru::Config &json) const override;
        bool DeserialiseAdd(Entity* pEntity, const configuru::Config &json) const override;
    };

    class ModelComponent: public EntityComponent
    {
        public:
        ModelComponent();
        ModelComponent(const ModelComponent &rhs);

        virtual void Init() override;
        static EntityComponentSerialiser * const Seriaialiser();

        void SetModel(Model * const model);
        Model* const ModelHandle() const;
        Renderable* const GetRenderable() const;

        public:

        private:
        Model *m_model;
        static ModelComponentSerialiser m_serialiser;
    };
}

#endif
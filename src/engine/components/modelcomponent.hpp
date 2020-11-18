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
        virtual bool Deserialise(EntityComponent* pComponent, const ContentEntityComponentInfo * pComponentInfo) const override;
        virtual bool DeserialiseAdd(Entity* pEntity, const ContentEntityComponentInfo * pComponentInfo) const override;
    };

    class ModelComponent: public EntityComponent
    {
        public:
        ModelComponent();
        ModelComponent(const ModelComponent &rhs);
        virtual ~ModelComponent();

        virtual void Init() override;
        virtual std::unique_ptr<Engine::EntityComponent> Duplicate() const override;

        void SetModel(Model * const model);
        Model* const ModelHandle() const;
        Renderable* const GetRenderable() const;

        public:
        std::string m_modelName;

        private:
        Model *m_model;
    };
}

#endif
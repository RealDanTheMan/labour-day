#ifndef MODEL_COMPONENT_HPP_
#define MODEL_COMPONENT_HPP_


#include "../entity.hpp"
#include "../entityserialiser.hpp"
#include "../modelinstance.hpp"
#include "../renderable.hpp"
#include "transformcomponent.hpp"

namespace Engine
{
    namespace Components
    {
        class ModelComponentSerialiser : public EntityComponentSerialiser
        {
            public:
            ModelComponentSerialiser();
            virtual ~ModelComponentSerialiser();
            virtual bool Deserialise(EntityComponent* pComponent, const ContentEntityComponentInfo * pComponentInfo) const override;
            virtual bool DeserialiseAdd(Entity* pEntity, const ContentEntityComponentInfo * pComponentInfo) const override;
        };

        class ModelComponent: public TransformComponent
        {
            public:
            ModelComponent();
            ModelComponent(const ModelComponent &rhs);
            virtual ~ModelComponent();

            virtual void Init() override;
            virtual std::unique_ptr<Engine::EntityComponent> Duplicate() const override;

            void SetModel(Model * model);
            ModelInstance * GetModelInstance();
            const ModelInstance * GetModelInstance() const;
            const Model * GetModel() const;
            void OnTransformChanged(const Transform &tr) override;

            public:
            std::string m_modelName;

            private:
            std::unique_ptr<ModelInstance> m_modelInstance; 
        };
    }
}

#endif
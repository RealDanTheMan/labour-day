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
            
            virtual bool Deserialise(
                EntityComponent *pComponent, 
                const ContentEntityComponentInfo *pComponentInfo,
                const ResourceCache *pResourceCache) const override;

            virtual bool DeserialiseAdd(
                Entity *pEntity, 
                const ContentEntityComponentInfo *pComponentInfo,
                const ResourceCache *pResourceCache) const override;
        };

        class ModelComponent: public TransformComponent, IModelRef
        {
            public:
            ModelComponent();
            ModelComponent(const ModelComponent &rhs);
            virtual ~ModelComponent();

            virtual void Init() override;
            virtual std::unique_ptr<Engine::EntityComponent> Duplicate() const override;

            ModelInstance * GetModelInstance();
            const ModelInstance * GetModelInstance() const;
            void OnTransformChanged(const Transform &tr) override;

            // IModelRef interface impl
            virtual void SetModel(Model *pModel) override;
            virtual void SetModelRefName(const std::string &name) override;
            virtual const Model * GetModel() const override;
            virtual const std::string & GetModelRefName() const override;
            virtual const bool InternalModelRefOnly() const;

            private:
            std::unique_ptr<ModelInstance> m_modelInstance; 
            std::string m_modelName;
        };
    }
}

#endif
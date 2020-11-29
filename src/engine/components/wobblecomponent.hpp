#ifndef TRANSFORM_WOBBLE_COMPONENT_H_
#define TRANSFORM_WOBBLE_COMPONENT_H_

#include "../entity.hpp"
#include "../entityserialiser.hpp"

namespace Engine::Components
{
    class WobbleComponentSerialiser : public EntityComponentSerialiser
    {
        public:
        WobbleComponentSerialiser();
        virtual ~WobbleComponentSerialiser();
        virtual bool Deserialise(EntityComponent* pComponent, const ContentEntityComponentInfo * pComponentInfo) const override;
        virtual bool DeserialiseAdd(Entity* pEntity, const ContentEntityComponentInfo * pComponentInfo) const override;
    };

    class WobbleComponent: public EntityComponent
    {
        public:
        WobbleComponent();
        WobbleComponent(const WobbleComponent &rhs);
        virtual ~WobbleComponent();

        virtual void Init() override;
        virtual std::unique_ptr<Engine::EntityComponent> Duplicate() const override;

        bool DoRotate() const;
        bool DoScale() const;
        float RotationSpeed() const;
        float ScaleSpeed() const;

        void ToggleRotation(const bool toggle);
        void ToggleScale(const bool toggle);
        void SetRotationSpeed(const float speed);
        void SetScaleSpeed(const float speed);

        private:

        bool m_doRotate;
        bool m_doScale;
        float m_rotationSpeed;
        float m_scaleSpeed;
        float m_scaleT;
    };
}

#endif
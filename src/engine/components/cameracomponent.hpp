#ifndef CAMERA_COMPONENT_HPP_
#define CAMERA_COMPONENT_HPP_

#include "../entitycomponent.hpp"
#include "../entityserialiser.hpp"
#include "../transform.hpp"
#include "../camera.hpp"

namespace Engine
{
    namespace Components
    {
        class CameraComponentSerialiser : public EntityComponentSerialiser
        {
            public:
            CameraComponentSerialiser();
            virtual ~CameraComponentSerialiser() override ; 
            virtual bool Deserialise(EntityComponent* pComponent, const ContentEntityComponentInfo * pComponentInfo) const override;
            virtual bool DeserialiseAdd(Entity* pEntity, const ContentEntityComponentInfo * pComponentInfo) const override;
        };

        class CameraComponent: public EntityComponent
        {
            public:
            CameraComponent();
            CameraComponent(const CameraComponent &rhs);
            virtual ~CameraComponent();
            virtual std::unique_ptr<EntityComponent> Duplicate() const override;
            virtual void Init() override;
            
            void SetActive(const bool active);
            bool IsActive() const;
            Transform & GetTransform();

            void SetNearClip(const float val);
            void SetFarClip(const float val);
            void SetFOV(const float val);
            void SetAspect(const float val);

            const float GetNearClip() const;
            const float GetFarClip() const;
            const float GetFOV() const;
            const float GetAspect() const;
            const Camera * const CameraHandle() const;

            void OnTransformChanged(int);
            ChangedDelegate OnTransformChangedDelegate;


            private:
            void UpdateTransform();

            Camera m_cam;
            Transform m_tr;
            bool m_isActive;
        };
    }
}

#endif
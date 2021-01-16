#ifndef LIGHT_COMPONENT_HPP_
#define LIGHT_COMPONENT_HPP_

#include "../lights.hpp"
#include "../entitycomponent.hpp"
#include "transformcomponent.hpp"

namespace Engine
{
    namespace Components
    {
        class LightComponent : public TransformComponent
        {
            public:
            LightComponent();
            LightComponent(const LightComponent &rhs);
            virtual ~LightComponent() override;

            virtual void Init() override;
            virtual std::unique_ptr<EntityComponent> Duplicate() const override;
            virtual void OnTransformChanged(const Transform &tr) override;

            void SetType(Light::LightType type);
            
            Light::LightType GetType() const;
            Light * GetLight();

            private:
            std::unique_ptr<Light> m_light;
        };
    }
}

#endif
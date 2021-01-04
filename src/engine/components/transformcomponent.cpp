#include "transformcomponent.hpp"

using namespace Engine::Components;

TransformComponentSerialiser::TransformComponentSerialiser() : EntityComponentSerialiser("TransformComponentClass")
{

}

TransformComponentSerialiser::~TransformComponentSerialiser()
{

}

bool TransformComponentSerialiser::Deserialise(EntityComponent* pComponent, const ContentEntityComponentInfo * pComponentInfo) const
{
    assert (pComponent != nullptr);

    auto pCmp = reinterpret_cast<TransformComponent*>(pComponent);
    assert (pCmp != nullptr);

    for(uint32_t i=0; i<pComponentInfo->m_properties.size(); i++)
    {
        const ContentPropertyInfo* pPropertyInfo = pComponentInfo->m_properties[i].get();

        if(pPropertyInfo->m_name == "Translation")
        {
            Vec3 translation = SerialisationUtils::Vec3FromString(pPropertyInfo->m_value);
            pCmp->GetTransform().SetTranslation(translation);
        }

        if(pPropertyInfo->m_name == "Rotation")
        {
            Vec3 rotation = SerialisationUtils::Vec3FromString(pPropertyInfo->m_value);
            pCmp->GetTransform().SetRotation(rotation);
        }

        if(pPropertyInfo->m_name == "Scale")
        {
            Vec3 scale = SerialisationUtils::Vec3FromString(pPropertyInfo->m_value);
            pCmp->GetTransform().SetScale(scale);
        }
    }

    return true;
}

bool TransformComponentSerialiser::DeserialiseAdd(Entity* pEntity, const ContentEntityComponentInfo * pComponentInfo) const
{
    assert (pEntity != nullptr);
    assert (pComponentInfo != nullptr);
    auto pCmp = pEntity->Components().Add<TransformComponent>();
    assert (pCmp != nullptr);

    bool stat = Deserialise(pCmp, pComponentInfo);
    if(stat)
    {
        return true;
    }

    return false;
}

TransformComponent::~TransformComponent()
{

}

void TransformComponent::Init()
{

}

std::unique_ptr<Engine::EntityComponent> TransformComponent::Duplicate() const
{
    auto dup = std::make_unique<TransformComponent>(*this);
    return dup;
}

Engine::Transform & TransformComponent::GetTransform()
{
    return m_tr;
}

const Engine::Transform & TransformComponent::GetTransform() const
{
    return m_tr;
}
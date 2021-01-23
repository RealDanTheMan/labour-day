#include "cameracomponent.hpp"

using namespace Engine::Components;

CameraComponentSerialiser::CameraComponentSerialiser() : EntityComponentSerialiser("CameraComponentClass")
{
}

CameraComponentSerialiser::~CameraComponentSerialiser()
{
}

bool CameraComponentSerialiser::Deserialise(
    EntityComponent* pComponent, 
    const ContentEntityComponentInfo * pComponentInfo,
    const ResourceCache *pResourceCache) const
{
    assert (pComponent != nullptr);

    auto pCom = reinterpret_cast<CameraComponent*>(pComponent);
    assert (pCom != nullptr);

    for(uint32_t i=0; i<pComponentInfo->m_properties.size(); i++)
    {
        const ContentPropertyInfo* pPropertyInfo = pComponentInfo->m_properties[i].get();
        if(pPropertyInfo->m_name == "IsActive")
        {
            bool isActive = SerialisationUtils::BoolFromString(pPropertyInfo->m_value);
            pCom->SetActive(isActive);
        }

        if(pPropertyInfo->m_name == "NearClip")
        {
            float nearClip = stof(pPropertyInfo->m_value, nullptr);
            pCom->SetNearClip(nearClip);
        }

        if(pPropertyInfo->m_name == "FarClip")
        {
            float farClip = stof(pPropertyInfo->m_value, nullptr);
            pCom->SetFarClip(farClip);
        }

        if(pPropertyInfo->m_name == "FOV")
        {
            float fov = stof(pPropertyInfo->m_value, nullptr);
            pCom->SetFOV(fov);
        }

        if(pPropertyInfo->m_name == "Aspect")
        {
            float aspect = stof(pPropertyInfo->m_value, nullptr);
            pCom->SetAspect(aspect);
        }

        if(pPropertyInfo->m_name == "OffsetTranslation")
        {
            Vec3 offset = SerialisationUtils::Vec3FromString(pPropertyInfo->m_value);
            pCom->SetOffsetTranslation(offset);
        }

        if(pPropertyInfo->m_name == "OffsetRotation")
        {
            Vec3 offset = SerialisationUtils::Vec3FromString(pPropertyInfo->m_value);
            pCom->SetOffsetRotation(offset);
        }
    }

    return true;
}

bool CameraComponentSerialiser::DeserialiseAdd(
    Entity* pEntity, 
    const ContentEntityComponentInfo * pComponentInfo,
    const ResourceCache *pResourceCache) const
{
    assert (pEntity != nullptr);
    assert (pComponentInfo != nullptr);
    auto pCom = pEntity->Components().Add<CameraComponent>();
    assert (pCom != nullptr);

    bool stat = Deserialise(pCom, pComponentInfo, pResourceCache);
    if(stat)
    {
        return true;
    }

    return false;
}

CameraComponent::CameraComponent():
m_isActive(false)
{
    // Some default camera values that work
    SetFOV(30.0f);
    SetAspect(1.77777);
}

CameraComponent::CameraComponent(const CameraComponent &rhs):
m_isActive(rhs.m_isActive),
m_cam(rhs.m_cam),
m_offset(rhs.m_offset)
{

}

CameraComponent::~CameraComponent()
{

}

void CameraComponent::SetActive(const bool active)
{
    m_isActive = active;
}

void CameraComponent::SetNearClip(const float val)
{
    m_cam.SetNearClip(val);
}

void CameraComponent::SetFarClip(const float val)
{
    m_cam.SetFarClip(val);
}

void CameraComponent::SetFOV(const float val)
{
    m_cam.SetFOV(val);
}

void CameraComponent::SetAspect(const float val)
{
    m_cam.SetAspect(val);
}

void CameraComponent::SetOffsetTranslation(const Vec3 &offset)
{
    m_offset.SetTranslation(offset);
}

void CameraComponent::SetOffsetRotation(const Vec3 &offset)
{
    m_offset.SetRotation(offset);
}

bool CameraComponent::IsActive() const
{
    return m_isActive;
}

const float CameraComponent::GetNearClip() const
{
    return m_cam.GetNearClip();
}

const float CameraComponent::GetFarClip() const
{
    return m_cam.GetFarClip();
}

const float CameraComponent::GetFOV() const
{
    return m_cam.GetFOV();
}

const float CameraComponent::GetAspect() const
{
    return m_cam.GetAspect();
}

Vec3 CameraComponent::GetOffsetTranslation() const
{
    return m_offset.Translation();
}

Vec3 CameraComponent::GetOffsetRotation() const
{
    return m_offset.Rotation();
}

const Engine::Camera * const CameraComponent::CameraHandle() const
{
    return &m_cam;
}

void CameraComponent::Init()
{

}

std::unique_ptr<Engine::EntityComponent> CameraComponent::Duplicate() const
{
    auto dup = std::make_unique<CameraComponent>(*this);
    return dup;
}

void CameraComponent::OnTransformChanged(const Transform &tr)
{
    Transform global(tr);
    global.TransformBy(m_offset);
    m_cam.SetTransform(global);
}
#include "cameracomponent.hpp"

using namespace Engine::Components;

CameraComponentSerialiser::CameraComponentSerialiser() : EntityComponentSerialiser("CameraComponentClass")
{
}

CameraComponentSerialiser::~CameraComponentSerialiser()
{
}

bool CameraComponentSerialiser::Deserialise(EntityComponent* pComponent, const ContentEntityComponentInfo * pComponentInfo) const
{
    assert (pComponent != nullptr);

    auto pCmp = reinterpret_cast<CameraComponent*>(pComponent);
    assert (pCmp != nullptr);

    for(uint32_t i=0; i<pComponentInfo->m_properties.size(); i++)
    {
        const ContentPropertyInfo* pPropertyInfo = pComponentInfo->m_properties[i].get();
        if(pPropertyInfo->m_name == "IsActive")
        {
            if(pPropertyInfo->m_value == "true" || pPropertyInfo->m_value == "1")
            {
                pCmp->SetActive(true);
            }
            else
            {
                pCmp->SetActive(false);
            }
        }

        if(pPropertyInfo->m_name == "NearClip")
        {
            float nearClip = stof(pPropertyInfo->m_value, nullptr);
            pCmp->SetNearClip(nearClip);
        }

        if(pPropertyInfo->m_name == "FarClip")
        {
            float farClip = stof(pPropertyInfo->m_value, nullptr);
            pCmp->SetFarClip(farClip);
        }

        if(pPropertyInfo->m_name == "FOV")
        {
            float fov = stof(pPropertyInfo->m_value, nullptr);
            pCmp->SetFOV(fov);
        }

        if(pPropertyInfo->m_name == "Aspect")
        {
            float aspect = stof(pPropertyInfo->m_value, nullptr);
            pCmp->SetAspect(aspect);
        }
    }

    return true;
}

bool CameraComponentSerialiser::DeserialiseAdd(Entity* pEntity, const ContentEntityComponentInfo * pComponentInfo) const
{
    assert (pEntity != nullptr);
    assert (pComponentInfo != nullptr);
    auto pCmp = pEntity->Components().Add<CameraComponent>();
    assert (pCmp != nullptr);

    bool stat = Deserialise(pCmp, pComponentInfo);
    if(stat)
    {
        return true;
    }

    return false;
}

CameraComponent::CameraComponent():
m_isActive(false),
m_tr(Engine::Transform()),
OnTransformChangedDelegate(ChangedDelegate(std::bind(&CameraComponent::OnTransformChanged, this, std::placeholders::_1)))
{
    // Some default camera values that work
    SetFOV(30.0f);
    SetAspect(1.77777);
    GetTransform().ChangedEvent().AddHandler(&OnTransformChangedDelegate);
}

CameraComponent::CameraComponent(const CameraComponent &rhs):
m_isActive(rhs.m_isActive),
m_tr(Engine::Transform(rhs.m_tr)),
m_cam(rhs.m_cam),
OnTransformChangedDelegate(rhs.OnTransformChangedDelegate)
{
    GetTransform().ChangedEvent().AddHandler(&OnTransformChangedDelegate);
}

CameraComponent::~CameraComponent()
{
    GetTransform().ChangedEvent().RemoveHandler(&OnTransformChangedDelegate);
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

Engine::Transform & CameraComponent::GetTransform()
{
    return m_tr;
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

void CameraComponent::UpdateTransform()
{
    m_cam.SetTransform(m_tr);
}

void CameraComponent::OnTransformChanged(int param)
{
    UpdateTransform();
}
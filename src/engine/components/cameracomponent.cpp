#include "cameracomponent.hpp"

using namespace Engine::Components;

CameraComponent::CameraComponent():
m_isActive(false),
m_cam(std::make_unique<Engine::Camera>())
{
    // Some default camera values that work
    SetFOV(30.0f);
    SetAspect(1.77777);
}

CameraComponent::CameraComponent(const CameraComponent &rhs):
m_isActive(rhs.m_isActive),
m_tr(Engine::Transform()),
m_cam(std::make_unique<Engine::Camera>(*rhs.m_cam))
{
    SetNearClip(rhs.GetNearClip());
    SetFarClip(rhs.GetFarClip());
    SetFOV(rhs.GetFOV());
    SetAspect(rhs.GetAspect());
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
    assert (m_cam != nullptr);
    m_cam->SetNearClip(val);
}

void CameraComponent::SetFarClip(const float val)
{
    assert (m_cam != nullptr);
    m_cam->SetFarClip(val);
}

void CameraComponent::SetFOV(const float val)
{
    assert (m_cam != nullptr);
    m_cam->SetFOV(val);
}

void CameraComponent::SetAspect(const float val)
{
    assert (m_cam != nullptr);
    m_cam->SetAspect(val);
}

bool CameraComponent::IsActive() const
{
    return m_isActive;
}

const float CameraComponent::GetNearClip() const
{
    assert (m_cam != nullptr);
    return m_cam->GetNearClip();
}

const float CameraComponent::GetFarClip() const
{
    assert (m_cam != nullptr);
    return m_cam->GetFarClip();
}

const float CameraComponent::GetFOV() const
{
    assert (m_cam != nullptr);
    return m_cam->GetFOV();
}

const float CameraComponent::GetAspect() const
{
    assert (m_cam != nullptr);
    return m_cam->GetAspect();
}

Engine::Transform & CameraComponent::GetTransform()
{
    return m_tr;
}

const Engine::Camera * const CameraComponent::CameraHandle() const
{
    return m_cam.get();
}

void CameraComponent::Init()
{

}

std::unique_ptr<Engine::EntityComponent> CameraComponent::Duplicate() const
{
    auto dup = std::make_unique<CameraComponent>();
    dup->m_tr = m_tr;
    dup->m_isActive = m_isActive;

    return dup;
}

void CameraComponent::UpdateTransform()
{
    assert (m_cam != nullptr);
    m_cam->SetTransform(m_tr);
}
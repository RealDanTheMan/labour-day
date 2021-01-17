#include "lightscache.hpp"
#include <algorithm>

using namespace Engine;

LightsCache::LightsCache():
m_sunLight(nullptr)
{
    
}

void LightsCache::Add(Light * pLight)
{
    m_lights.push_back(pLight);
    if(GetSunLight() == nullptr && pLight->GetType() == Light::LightType::Directional)
    {
        DirectionalLight *pSunlight = dynamic_cast<DirectionalLight*>(pLight);
        assert (pSunlight != nullptr);

        SetSunLight(pSunlight);
    }
}

void LightsCache::SetSunLight(DirectionalLight * pLight)
{
    m_sunLight = pLight;
}

void LightsCache::Remove(Light * pLight)
{
    m_lights.erase(std::remove(
            m_lights.begin(), 
            m_lights.end(), pLight), 
            m_lights.end());
}

void LightsCache::Clear()
{
    m_lights.clear();
}

const Light * LightsCache::Get(const uint32_t idx) const
{
    assert (idx < m_lights.size());
    return m_lights[idx];
}

const DirectionalLight * LightsCache::GetSunLight() const
{
    return m_sunLight;
}

const uint32_t LightsCache::Count() const
{
    return m_lights.size();
}
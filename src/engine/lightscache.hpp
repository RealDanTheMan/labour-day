#ifndef LIGHTS_CACHE_HPP_
#define LIGHTS_CACHE_HPP_

#include "lights.hpp"
#include <vector>

namespace Engine
{
    class LightsCache
    {
        public:
        LightsCache() = default;
        LightsCache(const LightsCache &rhs) = default;

        void Add(Light * pLight);
        void Remove(Light * pLight);
        void Clear();
        void SetSunLight(DirectionalLight * pLight);

        const DirectionalLight * GetSunLight() const;
        const Light * Get(const uint32_t idx) const;
        const uint32_t Count() const;

        private:
        DirectionalLight * m_sunLight;
        std::vector<Light*> m_lights;
    };
}

#endif
#ifndef SHADOWMAP_RENDERER_HPP_
#define SHADOWMAP_RENDERER_HPP_

#include "shadowframebuffer.hpp"
#include "modelinstance.hpp"

namespace Engine
{
    struct ShadowmapSettings
    {
        uint32_t m_resx;
        uint32_t m_resy;
    };

    class ShadowmapRenderer
    {
        public:
        ShadowmapRenderer() = default;
        ShadowmapRenderer(const ShadowmapRenderer &rhs) = delete;

        void Init(const ShadowmapSettings &settings);
        void RenderShadows(std::vector<const ModelInstance*> &instances) const;
        bool Ready() const;

        private:
        void DrawIntoShadowMap(const ModelInstance *instance) const;
        bool m_ready;
        std::unique_ptr<ShadowFrameBuffer> m_fb;
    };
}

#endif
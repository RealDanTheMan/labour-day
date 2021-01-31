#ifndef COMMON_RENDERER_H_
#define COMMON_RENDERER_H_

#include "components/modelcomponent.hpp"
#include "components/transformcomponent.hpp"
#include "igraphicsutils.hpp"
#include "dynamicrenderable.hpp"
#include "camera.hpp"
#include "lights.hpp"
#include "runtimeshaders.hpp"
#include "ecssys.hpp"
#include "lightscache.hpp"
#include "shadowmaprenderer.hpp"
#include <vector>

namespace Engine
{
    enum DrawMode
    {
        Fill,
        Wireframe,
        Line
    };

    struct RenderSettings
    {
        uint32_t m_resx;
        uint32_t m_resy;
        bool m_wireframe;
        bool m_shadows;
    };

    class CommonRenderer : public IGraphicsUtils
    {
        public:

        CommonRenderer(const RuntimeShaders * const rtShaders, const RenderSettings &settings);

        void Clear() const;
        void DrawRenderables() const;
        void DrawRenderable(const Renderable *renderable, const Transform* tr, const DrawMode mode, const Material * const mat) const;
        void DrawModelInstance(const ModelInstance *instance) const;
        void DrawLocator(const Transform * tr) const;
        void DrawModelComponents(ECSSys *ecs) const;
        void DrawTransformComponents(ECSSys *ecs) const;
        void DrawLightComponents(ECSSys * ecs) const;

        void ClearQueue();
        void AddToQueue(const Renderable *renderable);
        void SetCamera(const Camera *cam);
        void SetRenderSettings(const RenderSettings &settings);

        const Camera * const GetCamera() const;
        const RenderSettings & GetRenderSettings() const;
        const LightsCache & GetLightsCache() const;
        LightsCache & GetLightsCache();
        const DirectionalLight * GetMainLight() const;
        
        // IGraphicsUtils interface Impl
        virtual Vec3 NDCToWorld(const Vec2 &ndc) const override;
        virtual uint32_t ResolutionX() const override;
        virtual uint32_t ResolutionY() const override;
        virtual void DrawLineGizmo (const Vec3 &from, const Vec3 &to) const override;

        private:

        void PushUniformShaderParams(const ShaderProg *pShader, const Transform *transform) const;
        void PushLightShaderParams(const ShaderProg *pShader) const;
        void PushShadowShaderParams(const ShaderProg *pShader) const;
        void PushMaterialShaderParams(const ShaderProg &shader, const Material &mat) const;
        void BindMaterialTextures(const ShaderProg &shader, const Material &mat) const;
        void UnbindMaterialTextures(const ShaderProg &shader, const Material &mat) const;
        std::vector<const Renderable*> m_queue;
        const Camera* m_activeCam;
        const RuntimeShaders * const m_runtimeShaders;
        std::unique_ptr<Renderable> m_locator;
        std::unique_ptr<DynamicRenderable> m_line;
        RenderSettings m_settings;
        LightsCache m_lightsCache;
        DirectionalLight m_defaultLight;
        std::unique_ptr<ShadowmapRenderer> m_shadowRenderer;

    };
}

#endif
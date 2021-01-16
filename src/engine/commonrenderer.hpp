#ifndef COMMON_RENDERER_H_
#define COMMON_RENDERER_H_

#include "components/modelcomponent.hpp"
#include "components/transformcomponent.hpp"
#include "camera.hpp"
#include "lights.hpp"
#include "runtimeshaders.hpp"
#include "ecssys.hpp"
#include "lightscache.hpp"
#include <vector>

namespace Engine
{
    enum DrawMode
    {
        Fill,
        Wireframe
    };

    struct RenderSettings
    {
        bool m_wireframe;
    };

    class CommonRenderer
    {
        public:

        CommonRenderer(const RuntimeShaders * const rtShaders);

        void Clear() const;
        void DrawRenderables() const;
        void DrawRenderable(const Renderable *renderable, const Transform* tr, const DrawMode mode, const Material * const mat) const;
        void DrawModel(const Components::ModelComponent *model) const;
        void DrawModelWire(const Components::ModelComponent *model) const;
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

        private:

        void PushUniformShaderParams(const ShaderProg *shader, const Transform *transform) const;
        void PushLightShaderParams(const ShaderProg *shader) const;
        void PushMaterialShaderParams(const ShaderProg &shader, const Material &mat) const;
        void BindMaterialTextures(const ShaderProg &shader, const Material &mat) const;
        void UnbindMaterialTextures(const ShaderProg &shader, const Material &mat) const;
        std::vector<const Renderable*> m_queue;
        const Camera* m_activeCam;
        const RuntimeShaders * const m_runtimeShaders;
        std::unique_ptr<Renderable> m_locator;
        RenderSettings m_settings;
        LightsCache m_lightsCache;
        DirectionalLight m_defaultLight;

    };
}

#endif
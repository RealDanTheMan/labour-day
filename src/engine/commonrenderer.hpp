#ifndef COMMON_RENDERER_H_
#define COMMON_RENDERER_H_

#include "components/modelcomponent.hpp"
#include "components/transformcomponent.hpp"
#include "camera.hpp"
#include "runtimeshaders.hpp"
#include "ecssys.hpp"
#include <vector>

namespace Engine
{
    enum DrawMode
    {
        Fill,
        Wireframe
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

        void ClearQueue();
        void AddToQueue(const Renderable *renderable);
        void SetCamera(const Camera *cam);

        const Camera * const GetCamera() const;

        private:

        void PushUniformShaderParams(const ShaderProg *shader, const Transform *transform) const;
        void PushMaterialShaderParams(const ShaderProg &shader, const Material &mat) const;
        void BindMaterialTextures(const ShaderProg &shader, const Material &mat) const;
        void UnbindMaterialTextures(const ShaderProg &shader, const Material &mat) const;
        std::vector<const Renderable*> m_queue;
        const Camera* m_activeCam;
        const RuntimeShaders * const m_runtimeShaders;
        std::unique_ptr<Renderable> m_locator;
    };
}

#endif
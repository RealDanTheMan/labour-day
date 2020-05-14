#ifndef COMMON_RENDERER_H_
#define COMMON_RENDERER_H_

#include "components/modelcomponent.hpp"
#include "camera.hpp"
#include "runtimeshaders.hpp"
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
        void DrawRenderable(const Renderable *renderable, const Transform* tr, const DrawMode mode) const;
        void DrawModel(const Components::ModelComponent *model) const;
        void DrawModelWire(const Components::ModelComponent *model) const;
        void ClearQueue();
        void AddToQueue(const Renderable *renderable);
        void SetCamera(const Camera *cam);

        private:

        void PushUniformShaderParams(const ShaderProg *shader, const Transform *transform) const;
        std::vector<const Renderable*> m_queue;
        const Camera* m_activeCam;
        const RuntimeShaders * const m_runtimeShaders;
    };
}

#endif
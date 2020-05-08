#ifndef COMMON_RENDERER_H_
#define COMMON_RENDERER_H_

#include "components/modelcomponent.hpp"
#include "camera.hpp"
#include <vector>

namespace Engine
{
    class CommonRenderer
    {
        public:

        void Clear() const;
        void DrawRenderables() const;
        void DrawRenderable(const Renderable *renderable) const;
        void DrawModel(const Components::ModelComponent *model) const;
        void ClearQueue();
        void AddToQueue(const Renderable *renderable);
        void SetCamera(const Camera *cam);

        private:

        void PushUniformShaderParams(const ShaderProg *shader) const;
        std::vector<const Renderable*> m_queue;
        const Camera* m_activeCam;
    };
}

#endif
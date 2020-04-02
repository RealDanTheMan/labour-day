#ifndef COMMON_RENDERER_H_
#define COMMON_RENDERER_H_

#include "renderable.hpp"
#include "camera.hpp"
#include <vector>

namespace Engine
{
    class CommonRenderer
    {
        public:

        void Clear() const;
        void DrawRenderables() const;
        void ClearQueue();
        void AddToQueue(const Renderable *renderable);
        void SetCamera(const Camera *cam);

        private:

        void DrawRenderable(const Renderable *renderable) const;
        void PushUniformShaderParams(const ShaderProg *shader) const;
        std::vector<const Renderable*> m_queue;
        const Camera* m_activeCam;
    };
}

#endif
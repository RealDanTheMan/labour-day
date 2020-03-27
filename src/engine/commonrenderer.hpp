#ifndef COMMON_RENDERER_H_
#define COMMON_RENDERER_H_

#include "renderable.hpp"
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

        private:

        void DrawRenderable(const Renderable *renderable) const;
        std::vector<const Renderable*> m_queue;
    };
}

#endif
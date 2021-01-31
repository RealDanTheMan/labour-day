#ifndef DYNAMIC_RENDERABLE_HPP_
#define DYNAMIC_RENDERABLE_HPP_

#include "renderable.hpp"

namespace Engine
{
    class DynamicRenderable : public Engine::Renderable
    {
        public:

        void UpdateVertex(const uint32_t idx, const Vec3 &vertex);
        void UpdateNormal(const uint32_t idx, const Vec3 &normal);
        void UpdateTexcoord0(const uint32_t idx, const Vec2 &texcoord);
        void Update();

    };
}

#endif
#ifndef IGRAPHICS_UTILS_HPP_
#define IGRAPHICS_UTILS_HPP_

#include "types.hpp"

namespace Engine
{
    class IGraphicsUtils
    {
        public:
        IGraphicsUtils() = default;
        IGraphicsUtils(const IGraphicsUtils &rhs) = default;
        
        virtual uint32_t ResolutionX() const =0;
        virtual uint32_t ResolutionY() const =0;
        virtual Vec3 NDCToWorld(const Vec2 &ndc) const =0;
    };
}

#endif
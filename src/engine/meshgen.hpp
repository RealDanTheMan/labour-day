#ifndef MESHGEN_H_
#define MESHGEN_H_

#include "mesh.hpp"
#include <memory>

namespace Engine
{
    class MeshGen
    {
        public:

        static std::unique_ptr<Mesh> Triangle(const float scale);
    };
}

#endif
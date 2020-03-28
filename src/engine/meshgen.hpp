#ifndef MESHGEN_HPP_
#define MESHGEN_HPP_

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
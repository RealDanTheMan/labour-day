#ifndef MESHGEN_HPP_
#define MESHGEN_HPP_

#include "mesh.hpp"
#include <memory>
#include <string>

namespace Engine
{
    class MeshGen
    {
        public:

        static std::unique_ptr<Mesh> Triangle(const float scale);
        static std::unique_ptr<Mesh> Cube(const float scale);
        static std::unique_ptr<Mesh> Box(const float width, const float height, const float depth);
        static std::unique_ptr<Mesh> FromOBJ(const std::string &filepath);
    };
}

#endif
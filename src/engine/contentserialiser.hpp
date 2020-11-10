#ifndef CONTENT_SERIALISER_HPP_
#define CONTENT_SERIALISER_HPP_

#include "meshgen.hpp"
#include "model.hpp"
#include "material.hpp"
#include "texture2d.hpp"
#include "prefab.hpp"
#include "sysutils.hpp"

namespace Engine
{
    class ContentSerialiser
    {
        public:

        static std::unique_ptr<Mesh> LoadMesh(const std::string &filepath);
        static std::unique_ptr<Material> LoadMaterial(const std::string &filepath);
        static std::unique_ptr<Model> LoadModel(const std::string &filepath);
        static std::unique_ptr<Prefab> LoadPrefab(const std::string &filepath);
    };
}

#endif
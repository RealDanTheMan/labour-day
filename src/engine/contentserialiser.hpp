#ifndef CONTENT_SERIALISER_HPP_
#define CONTENT_SERIALISER_HPP_

#include "contentserialisation.hpp"
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
        static std::unique_ptr<ContentMaterialInfo> LoadMaterialInfo(const std::string &filepath);
        static std::unique_ptr<ContentModelInfo> LoadModelInfo(const std::string &filepath);
        static std::unique_ptr<ContentEntityInfo> LoadEntityInfo(const std::string &filepath);
        static std::unique_ptr<ContentManifestInfo> LoadManifestInfo(const std::string &filepath);
    };
}

#endif
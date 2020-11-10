#ifndef PREFAB_HPP_
#define PREFAB_HPP_

#include "iresource.hpp"
#include "entityserialiser.hpp"

#include <string>
#include <memory>

namespace Engine
{
    class Prefab : public IResource
    {
        public:
        Prefab(const Entity &entity);
        void Unload() override;

        const Entity* const PrefabEntity() const;

        private:
        std::unique_ptr<Entity> m_entity;

    };
}

#endif
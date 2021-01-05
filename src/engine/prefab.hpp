#ifndef PREFAB_HPP_
#define PREFAB_HPP_

#include "iresource.hpp"
#include "entity.hpp"
#include <string>
#include <memory>

namespace Engine
{
    class Prefab : public IResource
    {
        public:
        Prefab(const Entity &entity);
        Prefab(const std::vector<std::unique_ptr<Entity>> &entities);
        void Unload() override;
        std::vector<const Entity*> GetRootEntities() const;

        private:
        std::vector<std::unique_ptr<Entity>> m_entities;

    };
}

#endif
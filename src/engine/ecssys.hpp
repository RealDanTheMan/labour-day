#ifndef ECSSYS_HPP_
#define ECSSYS_HPP_


#include "types.hpp"
#include "entity.hpp"
#include "entityprocess.hpp"
#include "prefab.hpp"

#include <vector>
#include <memory>

namespace Engine
{
    class ECSSys
    {
        public:
        ECSSys();

        void Init(const uint32_t poolSize);
        void Update(const double deltaTime);
        void Terminate();

        Entity* CreateEntity();
        Entity* CreateEntity(const Prefab * const pref);

        template <typename T>
        T* const CreateProcess();

        template <typename T>
        void AssetsByComponent(std::vector<Entity*>& outVec);

        template <typename T>
        std::vector<T*> GetAllComponents();


        std::vector<Entity*> GetAllEntities();
        std::vector<EntityComponent*> GetAllComponentNotReady();


        private:
        std::vector<std::unique_ptr<Entity>> m_liveEntities;
        std::vector<std::unique_ptr<Entity>> m_pool;
        std::vector<std::unique_ptr<EntityComponent>> m_components;
        std::vector<std::unique_ptr<EntityProcess>> m_procs;
    };

    template <typename T>
    T* const ECSSys::CreateProcess()
    {
        static_assert (std::is_base_of<EntityProcess, T>::value, "Invalid template type, expected derived from <EntityProcess>");
        m_procs.push_back(std::make_unique<T>());
        return reinterpret_cast<T*>(m_procs.back().get());
    }

    template <typename T>
    void ECSSys::AssetsByComponent(std::vector<Entity*>& outVec)
    {
        static_assert (std::is_base_of<EntityComponent, T>::value, "Invalid template type, expected derived from <EntityComponent>");
        for(uint32_t i=0; i < m_liveEntities.size(); i++)
        {
            if(m_liveEntities[i]->Components().GetFirst<T>() != nullptr)
            {
                outVec.push_back(m_liveEntities[i].get());
            }
        }
    }

    template <typename T>
    std::vector<T*> ECSSys::GetAllComponents()
    {
        static_assert (std::is_base_of<EntityComponent, T>::value, "Invalid template type, expected derived from <EntityComponent>");
        std::vector<T*> coms;

        for(auto &entity : m_liveEntities)
        {
            std::vector<T*> entityComs = entity->Components().GetAll<T>();
            for(auto &com : entityComs)
            {
                coms.push_back(com);
            }
        }

        return coms;
    }
}

#endif
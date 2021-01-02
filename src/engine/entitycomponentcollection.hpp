#ifndef ENTITY_COMPONENT_COLLECTION_HPP_
#define ENTITY_COMPONENT_COLLECTION_HPP_


#include "entitycomponent.hpp"
#include <stdint.h>
#include <vector>
#include <memory>

namespace Engine
{
    class EntityComponentCollection
    {
        public:
            EntityComponentCollection();
            EntityComponentCollection(const EntityComponentCollection &rhs)=delete;

            const uint32_t Count() const;
            std::unique_ptr<EntityComponentCollection> Duplicate() const;
            
            template<typename T> 
            T* const  Add();

            template<typename T>
            T* const Get();

            template <typename T>
            std::vector<T*> GetAll();

        private:
            uint32_t m_count;
            std::vector<std::unique_ptr<EntityComponent>> m_components;
    };


    template <typename T>
    T* const EntityComponentCollection::Add()
    {
        static_assert (std::is_base_of<EntityComponent, T>::value, "Invalid template type, expected derived from <EntityComponent>");
        auto com = std::make_unique<T>();
        m_components.push_back(std::move(com));

        return dynamic_cast<T*>(m_components.back().get());
    }

    template<typename T>
    T* const EntityComponentCollection::Get()
    {
        static_assert (std::is_base_of<EntityComponent, T>::value, "Invalid template type, expected derived from <EntityComponent>");
        for(auto& com : m_components)
        {
            auto match = dynamic_cast<T*>(com.get());
            if(match)
            {
                return match;
            }
        }

        return nullptr;
    }

    template <typename T>
    std::vector<T*> EntityComponentCollection::GetAll()
    {
        static_assert (std::is_base_of<EntityComponent, T>::value, "Invalid template type, expected derived from <EntityComponent>");
        
        std::vector<T*> components;
        for(auto& com : m_components)
        {
            auto match = dynamic_cast<T*>(com.get());
            if(match)
            {
                components.push_back(match);
            }
        }

        return components;
    }
}

#endif
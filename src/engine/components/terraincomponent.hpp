#ifndef TERRAIN_COMPONENT_HPP_
#define TERRAIN_COMPONENT_HPP_

#include "../entitycomponent.hpp"
#include "modelcomponent.hpp"

namespace Engine
{
    namespace Components
    {
        class TerrainComponent : public ModelComponent
        {
            public:
            TerrainComponent() = default;
            TerrainComponent(const TerrainComponent &rhs) = delete;
            virtual ~TerrainComponent() override;

            virtual void Init() override;
            virtual std::unique_ptr<EntityComponent> Duplicate() const override;

            void SetTileSize(float size);
            void SetColumns(uint32_t columns);
            void SetRows(uint32_t rows);
            void SetMaterial(Engine::Material * mat);

            float GetTileSize() const;
            uint32_t GetColumns() const;
            uint32_t GetRows() const;

            private:
            float m_tileSize;
            uint32_t m_columns;
            uint32_t m_rows;

            std::unique_ptr<Engine::Model> m_terrModel;
            Engine::Material * m_mat;
        };
    }
}

#endif
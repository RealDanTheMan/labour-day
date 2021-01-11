#include "terraincomponent.hpp"
#include "../meshgen.hpp"

using namespace Engine::Components;

TerrainComponent::~TerrainComponent()
{

}

void TerrainComponent::Init()
{
    assert (GetTileSize() > 0.0f);
    assert (GetRows() > 0);
    assert (GetColumns() > 0);
    assert (m_mat != nullptr);

    const float width = GetTileSize() * GetRows();
    const float depth = GetTileSize() * GetColumns();

    // Generate terrain model geometry
    auto msh = Engine::MeshGen::Box(width, 0.1f, depth);
    m_terrModel = std::make_unique<Engine::Model>(*msh, m_mat);

    // Update model handle
    SetModel(m_terrModel.get());
}

std::unique_ptr<Engine::EntityComponent> TerrainComponent::Duplicate() const
{
    auto dup = std::make_unique<TerrainComponent>();
    dup->SetTileSize(GetTileSize());
    dup->SetColumns(GetColumns());
    dup->SetRows(GetRows());

    return dup;
}

void TerrainComponent::SetTileSize(float size)
{
    m_tileSize = size;
}

void TerrainComponent::SetColumns(uint32_t columns)
{
    m_columns = columns;
}

void TerrainComponent::SetRows(uint32_t rows)
{
    m_rows = rows;
}

void TerrainComponent::SetMaterial(Engine::Material * mat)
{
    m_mat = mat;

    // TODO : Update material on the terrain model !
    // For now we assert if someone updated material while the model 
    // resource is already generated !
    assert (m_terrModel == nullptr);
}

float TerrainComponent::GetTileSize() const
{
    return m_tileSize;
}

uint32_t TerrainComponent::GetColumns() const
{
    return m_columns;
}

uint32_t TerrainComponent::GetRows() const
{
    return m_rows;
}
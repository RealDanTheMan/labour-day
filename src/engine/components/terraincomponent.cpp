#include "terraincomponent.hpp"
#include "../meshgen.hpp"

using namespace Engine::Components;

TerrainComponentSerialiser::TerrainComponentSerialiser() : EntityComponentSerialiser("TerrainComponentClass")
{

}

TerrainComponentSerialiser::~TerrainComponentSerialiser()
{

}

bool TerrainComponentSerialiser::Deserialise(EntityComponent* pComponent, const ContentEntityComponentInfo * pComponentInfo) const
{
    assert (pComponent != nullptr);

    auto pCom = reinterpret_cast<TerrainComponent*>(pComponent);
    assert (pCom != nullptr);

    for(uint32_t i=0; i<pComponentInfo->m_properties.size(); i++)
    {
        const ContentPropertyInfo* pPropertyInfo = pComponentInfo->m_properties[i].get();
        if(pPropertyInfo->m_name == "TileSize")
        {
            float tileSize = SerialisationUtils::FloatFromString(pPropertyInfo->m_value);
            pCom->SetTileSize(tileSize);
            continue;
        }

        if(pPropertyInfo->m_name == "Columns")
        {
            uint32_t columns = SerialisationUtils::IntFromString(pPropertyInfo->m_value);
            pCom->SetColumns(columns);
            continue;
        }

        if(pPropertyInfo->m_name == "Rows")
        {
            uint32_t rows = SerialisationUtils::IntFromString(pPropertyInfo->m_value);
            pCom->SetRows(rows);
            continue;
        }
    }

    return true;
}

bool TerrainComponentSerialiser::DeserialiseAdd(Entity* pEntity, const ContentEntityComponentInfo * pComponentInfo) const
{
    assert (pEntity != nullptr);
    assert (pComponentInfo != nullptr);
    auto pCmp = pEntity->Components().Add<TerrainComponent>();
    assert (pCmp != nullptr);

    bool stat = Deserialise(pCmp, pComponentInfo);
    if(stat)
    {
        return true;
    }

    return false;
}

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
    ModelComponent::SetModel(m_terrModel.get());
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

void TerrainComponent::SetModel(Model *pModel)
{
    // Nothing
    // We dont want to override model reference from outside
    // This class mainatin its own model resource that is build at runtime
}

const bool TerrainComponent::InternalModelRefOnly() const
{
    return true;
}
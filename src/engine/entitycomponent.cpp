#include "entitycomponent.hpp"
#include "debugging.hpp"

using namespace Engine;


EntityComponent::~EntityComponent() {}

void EntityComponent::PreInit()
{
    Init();
    m_isReady = true;
}

bool EntityComponent::IsReady() const
{
    return m_isReady;
}
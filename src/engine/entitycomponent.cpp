#include "entitycomponent.hpp"
#include "debugging.hpp"

using namespace Engine;

std::map<std::string, EntityComponentDesc> EntityComponentFac::m_map = {};


bool EntityComponentFac::RegieterClass(const EntityComponentDesc &classDesc)
{
    assert (EntityComponentFac::m_map.find(classDesc.m_className) != EntityComponentFac::m_map.end());
    
    EntityComponentFac::m_map.insert(std::make_pair(classDesc.m_className, classDesc));
    return true;
}
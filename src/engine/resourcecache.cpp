#include "resourcecache.hpp"
#include <algorithm>

using namespace Engine;

void ResourceCache::Free()
{
    for(uint32_t i=0; i < m_resources.size(); i++)
    {
        assert (m_resources[i] != nullptr);

        m_resources[i]->Unload();
        m_resources[i].reset(nullptr);
    }

    m_resources.clear();
    m_keys.clear();
}

uint32_t ResourceCache::Count() const
{
    return m_resources.size();
}

bool ResourceCache::HasResourceKey(const std::string &key) const
{
    if(std::find(m_keys.begin(), m_keys.end(), key) != m_keys.end())
    {
        return true;
    }

    return false;
}

uint32_t ResourceCache::ResourceIdx(const std::string &key) const
{
    assert (HasResourceKey(key));

    std::vector<std::string>::const_iterator it = std::find(m_keys.begin(), m_keys.end(), key);
    return std::distance(m_keys.begin(), it);
}



IResource * const ResourceCache::GetResource(const std::string &key) const
{
    if(HasResourceKey(key))
    {
        const uint32_t idx = ResourceIdx(key);
        return m_resources[idx].get();
    }

    return nullptr;
}
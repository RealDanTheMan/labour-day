#include "tags.hpp"
#include "debugging.hpp"
#include <algorithm>

using namespace Engine;

void Tags::Add(const std::string &tag)
{
    if(!Has(tag))
    {
        m_tags.push_back(tag);
    }
}

void Tags::Remove(const std::string &tag)
{
    if(Has(tag))
    {
        m_tags.erase(std::remove(
            m_tags.begin(), 
            m_tags.end(), tag), 
            m_tags.end());
    }
}

bool Tags::Has(const std::string &tag) const
{
    if(std::find(m_tags.begin(), m_tags.end(), tag) != m_tags.end())
    {
        return true;
    }

    return false;
}

uint32_t Tags::Count() const
{
    return m_tags.size();
}

const std::string & Tags::Get(const uint32_t idx) const
{
    assert (idx < Count());
    return m_tags[idx];
}

#include "iresource.hpp"

using namespace Engine;

IResource::IResource():
m_uuid(0)
{

}

uint32_t IResource::UUID() const 
{
    return m_uuid;
}
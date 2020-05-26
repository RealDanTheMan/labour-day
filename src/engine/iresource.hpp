#ifndef RESOURCE_HPP_
#define RESOURCE_HPP_

#include "types.hpp"

namespace Engine
{
    class IResource
    {
        public:
        IResource();
        IResource(const IResource &rhs) = delete;

        uint32_t UUID() const;
        virtual void Unload() = 0;


        private:
        uint32_t m_uuid;
    };
}

#endif
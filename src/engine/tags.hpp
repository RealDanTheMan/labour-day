#ifndef TAGS_HPP_
#define TAGS_HPP_

#include <string>
#include <vector>

namespace Engine
{
    class Tags
    {
        public:
        Tags() = default;
        Tags(const Tags &rhs) = default;

        void Add(const std::string &tag);
        void Remove(const std::string &tag);
        bool Has(const std::string &tag) const;
        uint32_t Count() const;
        const std::string & Get(const uint32_t idx) const;

        private:
        std::vector<std::string> m_tags;
    };

    class ITagged
    {
        public:
        virtual Tags * GetTags() =0;
    };
}

#endif
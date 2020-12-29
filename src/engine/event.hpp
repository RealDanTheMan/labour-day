#ifndef EVENT_HPP_
#define EVENT_HPP_

#include <vector>
#include <algorithm>
#include "types.hpp"
#include "eventdelegate.hpp"

namespace Engine
{
    template <typename T>
    class Event 
    {
        public:
        Event<T>();
        Event<T>(const Event<T>& rhs);

        template <typename U>
        void Invoke(const U &args) const;
        void AddHandler(T * handler);
        void RemoveHandler(T * handler);

        private:
        std::vector<T*> m_delegates;
    };

    template <typename T>
    Event<T>::Event()
    {

    }

    template <typename T>
    Event<T>::Event(const Event<T>& rhs)
    {
        for(T* del : rhs.m_delegates)
        {
            m_delegates.push_back(del);
        }
    }

    template <typename T>
    void Event<T>::AddHandler(T * handler)
    {
        static_assert (std::is_base_of<IDelegate, T>::value, "Invalid template type, expected derived from <IDelegate>");
        m_delegates.push_back(handler);
    }

    template <typename T>
    void Event<T>::RemoveHandler(T * handler)
    {
        static_assert (std::is_base_of<IDelegate, T>::value, "Invalid template type, expected derived from <IDelegate>");
        m_delegates.erase(std::remove(m_delegates.begin(), m_delegates.end(), handler), m_delegates.end());
    }

    template <typename T>
    template <typename U>
    void Event<T>::Invoke(const U &args) const
    {
        static_assert (std::is_base_of<IDelegate, T>::value, "Invalid template type, expected derived from <IDelegate>");
        for(T * del : m_delegates)
        {
            auto idel = dynamic_cast<T*>(del);
            assert (idel != nullptr);

            idel->SetArgs(args);
            idel->Execute();
        }
    }
}

#endif
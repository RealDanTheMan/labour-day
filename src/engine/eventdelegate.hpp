#ifndef EVENT_DELEGATE_HPP_
#define EVENT_DELEGATE_HPP_

#include "debugging.hpp"
#include <functional>

namespace Engine
{
    class IDelegate 
    {
        public:
        virtual bool CanExecute() const = 0;
        virtual void Execute() const = 0;
    };

    template <typename ret, typename args>
    class EventDelegate : public IDelegate
    {
        public:
        EventDelegate<ret, args>(std::function<ret(args)> fn);
        EventDelegate<ret, args>(const EventDelegate<ret, args>& rhs);

        void Execute() const override;
        bool CanExecute() const override;
        void SetArgs(args arg);

        private:
        std::function<ret(args)> m_foo;
        args m_args;
    };
    
    template <typename ret, typename args>
    EventDelegate<ret, args>::EventDelegate(std::function<ret(args)> fn):
    m_foo(fn)
    {
    }

    template <typename ret, typename args>
    EventDelegate<ret, args>::EventDelegate(const EventDelegate<ret, args>& rhs):
    m_foo(rhs.m_foo),
    m_args(m_args)
    {
    }

    template <typename ret, typename args>
    void EventDelegate<ret, args>::Execute() const
    {
        if(CanExecute())
        {
            D_MSG("Calling event delegate std::function");
            m_foo(m_args);
        }
    }

    template <typename ret, typename args>
    bool EventDelegate<ret, args>::CanExecute() const
    {
        return true;
    }

    template <typename ret, typename args>
    void EventDelegate<ret, args>::SetArgs(args arg)
    {
        m_args = arg;
    } 
}

#endif
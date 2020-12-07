#ifndef GAME_TIME_HPP_
#define GAME_TIME_HPP_

#include <chrono>

namespace Engine
{
    class GameTime
    {
        public:

        // Returns time since the first tick in seconds
        const double CurrentTime() const;

        // Returns time in seconds since the last tick
        const double DeltaTime() const;
        void Tick();

        private:
        bool m_started;
        double m_currentTime;
        double m_deltaTime;

        std::chrono::system_clock::time_point m_startClk;
        std::chrono::system_clock::time_point m_currentClk;
        std::chrono::system_clock::time_point m_previousClk;
        

        // Returns system time in seconds since epoch
        static const double GetSysTime();
    };
}

#endif
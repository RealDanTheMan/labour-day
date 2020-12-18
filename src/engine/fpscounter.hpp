#ifndef FPS_COUNTER_HPP_
#define FPS_COUNTER_HPP_

#include "types.hpp"
#include <vector>
#include <chrono>

namespace Engine
{
    class FpsCounter
    {
        public:
        FpsCounter();
        void Sample();
        uint32_t Get() const;
        double GetMilliseconds() const;
        
        private:
        uint32_t m_maxSamples;
        double m_fps;
        double m_milliseconds;
        uint32_t m_currentSampleIdx;
        std::chrono::system_clock::time_point m_lastSampleTime;
        std::vector<double> m_samples;

    };
}

#endif
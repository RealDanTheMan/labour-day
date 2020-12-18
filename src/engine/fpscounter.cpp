#include "fpscounter.hpp"

using namespace Engine;

FpsCounter::FpsCounter():
m_maxSamples(8),
m_fps(0),
m_currentSampleIdx(0),
m_lastSampleTime(std::chrono::system_clock::now())
{
    // Set initial samples to zero
    for(uint32_t i=0; i < m_maxSamples; i++)
    {
        m_samples.push_back(0.00000001);
    }

    m_lastSampleTime = std::chrono::system_clock::now();
}

void FpsCounter::Sample()
{
    auto sample = std::chrono::system_clock::now();
    auto delta = std::chrono::duration_cast<std::chrono::duration<double>>(sample - m_lastSampleTime);
    m_samples[m_currentSampleIdx] = delta.count();
    m_currentSampleIdx = m_currentSampleIdx >= m_maxSamples ? 0 : m_currentSampleIdx += 1;
    m_lastSampleTime = sample;

    double time = 0.0;
    for(uint32_t i=0; i < m_maxSamples; i++)
    {
        time += m_samples[i];
    }

    assert (m_maxSamples > 0);
    assert (time > 0.0);

    // Average time in seconds per frame in the past n-frames
    time = (time / (double)m_maxSamples);

    // Convert to frames per second & milliseconds per frame
    m_milliseconds = time * 1000.0;
    m_fps = 1.0 / time;
}

uint32_t FpsCounter::Get() const
{
    return m_fps;
}

double FpsCounter::GetMilliseconds() const
{
    return m_milliseconds;
}

#include "gametime.hpp"
#include <ctime>
#include <ratio>

using namespace Engine;

const double GameTime::CurrentTime() const 
{
    return m_currentTime;
}

const double GameTime::DeltaTime() const
{
    return m_deltaTime;
}

void GameTime::Tick()
{
    if(!m_started)
    {
        // Grab reference time if this is the first tick
        m_startClk = std::chrono::high_resolution_clock::now();
        m_previousClk = m_startClk;
        m_currentClk = m_startClk;
        m_started = true;
    }

    m_previousClk = m_currentClk;
    m_currentClk = std::chrono::high_resolution_clock::now();

    auto time = std::chrono::duration_cast<std::chrono::duration<double>>(m_currentClk - m_startClk);
    auto delta = std::chrono::duration_cast<std::chrono::duration<double>>(m_currentClk - m_previousClk);

    m_deltaTime = delta.count();
    m_currentTime = time.count();
}

const double GameTime::GetSysTime ()
{
    auto clk = std::chrono::system_clock::now();
    auto seconds = std::chrono::system_clock::to_time_t(clk);

    return seconds;
}
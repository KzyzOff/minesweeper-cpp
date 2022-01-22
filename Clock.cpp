
#include "Clock.h"

Clock::Clock()
{
    init();
}

void Clock::init()
{
    m_running = false;
    m_duration = 0;
    m_start_timestamp = 0;
    m_stop_timestamp = 0;
}

void Clock::start()
{
    if (m_running) return;

	m_running = true;
	m_start_timestamp = SDL_GetTicks64();
}

void Clock::stop()
{
    if (!m_running) return;

	m_running = false;
    m_stop_timestamp = SDL_GetTicks64();
    m_duration += m_stop_timestamp - m_start_timestamp;
}

// Return time from start in milliseconds when called with default argument,
// seconds when called with 1000 as argument and so on
Uint64 Clock::duration(Uint64 divider) const
{
    if (!m_running)
    {
        return m_duration / divider;
    }
	return (m_duration + SDL_GetTicks64() - m_start_timestamp) / divider;
}

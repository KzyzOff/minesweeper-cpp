
#include "Clock.h"

Clock::Clock()
: m_start_timestamp(0),
  m_duration(0),
  m_running(false)
{}

void Clock::start()
{
	m_running = true;
	m_start_timestamp = SDL_GetTicks();
}

void Clock::stop()
{
	m_running = false;
	m_duration = SDL_GetTicks() - m_start_timestamp;
}

// Return time from start in milliseconds when called with default argument,
// seconds when called with 1000 as argument and so on
Uint64 Clock::fromStart(Uint64 divider) const
{
	return (SDL_GetTicks() - m_start_timestamp) / divider;
}

Uint64 Clock::duration(Uint64 divider) const
{
	return m_duration / divider;
}

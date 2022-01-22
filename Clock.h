
#ifndef MINESWEEPER_CLOCK_H
#define MINESWEEPER_CLOCK_H


#include "header.h"

// TODO: Clock should remember it's duration when stop() is called, and start from that duration when start() is called

class Clock
{
public:
	Clock();

    void init();
	void start();
	void stop();
	Uint64 fromStart(Uint64 divider = 1) const;
	Uint64 duration(Uint64 divider = 1) const;
	bool isRunning() const { return m_running; };

private:
	Uint64 m_start_timestamp;
	Uint64 m_duration;
	bool m_running;

};


#endif //MINESWEEPER_CLOCK_H

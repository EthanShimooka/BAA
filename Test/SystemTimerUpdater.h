#pragma once

#ifndef SYSTEMTIMERUPDATER_H_INCLUDED
#define SYSTEMTIMERUPDATER_H_INCLUDED

#include <vector>

class SystemTimerUpdater
{
public:
	///Constructor
	SystemTimerUpdater();
	///Deconstructor
	~SystemTimerUpdater();
	/// Updates all timers
	void TimerUpdate();

	//std::vector<Timer*> timers;
};

#endif
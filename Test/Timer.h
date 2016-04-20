#pragma once
#ifndef TIMER_H_INCLUDED
#define TIMER_H_INCLUDED

#include <time.h>

class Timer
{
public:
	Timer(float length);
	~Timer();
	void Update();
	clock_t startTime;
	clock_t timerLength;
	bool timing;
	void (*func); // need to add func paramater to constructor, have constructor add pointer to this timer to the list of timers in systemtimerupdater

};
#endif


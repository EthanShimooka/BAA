#pragma once
#ifndef TIMER_H_INCLUDED
#define TIMER_H_INCLUDED

#include <time.h>
#include <vector>

class Timer
{
public:
	/// Constructor, should be only call you need to make to create a timer, DO NOT CALL IN AN UPDATE UNLESS YOU TAKE PRECAUTIONS SO THAT IT IS ONLY CALLED ONCE WHEN YOU NEED IT
	Timer(float length, void(*functionToCall));
	/// Deconstructor, removes itself(instance of timer class) from list of timers
	~Timer();
	/// Updates this instance of a timer
	void Update();
	/// The saved initial time
	clock_t startTime;
	/// Duration of the timer until the specified function will be called
	clock_t timerLength;
	/// Bool whether or not the timer is counting down
	bool timing;
	/// Saved function reference of the function to be called after timerLength time
	void (*func);
	/// Static list of all timers that need to be updated
	static std::vector<Timer*> timers;
	/// Updates all timers in list of timers. 
	static void UpdateTimers();
};
#endif


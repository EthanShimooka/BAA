#pragma once
#ifndef INVOKE_H_INCLUDED
#define INVOKE_H_INCLUDED

#include <time.h>
#include <vector>
#include <iostream>

using function_m = void(*)();

class Invoke
{
public:
	/// Constructor, should be only call you need to make to create a timer, DO NOT CALL IN AN UPDATE UNLESS YOU TAKE PRECAUTIONS SO THAT IT IS ONLY CALLED ONCE WHEN YOU NEED IT
	Invoke(float length, function_m functionToCall);
	/// Deconstructor, removes itself(instance of timer class) from list of timers
	~Invoke();
	/// Updates all timers in list of timers. 
	static void UpdateTimers();
protected:
	/// Updates this instance of a timer
	void Update();
	/// The saved initial time
	clock_t startTime;
	/// Duration of the timer until the specified function will be called
	clock_t timerLength;
	/// Bool whether or not the timer is counting down
	bool timing;
	/// Saved function reference of the function to be called after timerLength time
	function_m func;
	/// Static list of all timers that need to be updated
	static std::vector<Invoke*> timers; //may need to move this to a different file
	
};

#endif


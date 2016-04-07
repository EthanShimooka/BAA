#include "include\network\NetIncludes.h"
#include <iostream>

float kDesiredFrameTime = 0.03333333f;
#if !_WIN32
#include <chrono>
using namespace std::chrono;
#endif

Timing	Timing::sInstance;

namespace{
#if _WIN32
	LARGE_INTEGER sStartTime = { 0 };
#else
	high_resolution_clock::time_point sStartTime;
#endif
}

Timing::Timing(){
#if _WIN32
	gameLengthInSeconds = 240;
	LARGE_INTEGER perfFreq;
	QueryPerformanceFrequency(&perfFreq);
	mPerfCountDuration = 1.0 / perfFreq.QuadPart;

	QueryPerformanceCounter(&sStartTime);

	mLastFrameStartTime = GetTime();
#else
	sStartTime = high_resolution_clock::now();
#endif
}

bool Timing::Update(){
	double currentTime = GetTime();

	mDeltaTime = (float)(currentTime - mLastFrameStartTime);

	//frame lock at 30fps
	while (mDeltaTime < kDesiredFrameTime)
	{
		//std::cout << "mDeltaTime = " << mDeltaTime << std::endl;
		currentTime = GetTime();

		mDeltaTime = (float)(currentTime - mLastFrameStartTime);
	}

	//set the delta time to the desired frame time, to try to account
	//for potential slight fluctuations that may occur when exiting the loop
	//this also will handle the frame time not going crazy if spammed with events
	mDeltaTime = kDesiredFrameTime;

	mLastFrameStartTime = currentTime;
	mFrameStartTimef = static_cast< float > (mLastFrameStartTime);
	return true;
}

void Timing::SetCountdownStart(){
	startTimeInSeconds = time(NULL);
	//std::cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@ Start Time(since epoch) = " << startTimeInSeconds << std::endl;
}

int Timing::GetTimeRemainingS(){
	double timeRemaining = 0;
	time_t now = time(NULL);
	time_t timeElapsed = now - startTimeInSeconds;
	//std::cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@ timeElapsed = " << timeElapsed << std::endl;
	//std::cout << "@@@@@@@@@@@@@@@@@ timeElapsed as int = " << (int)timeElapsed << std::endl;
	return gameLengthInSeconds - (int)timeElapsed;
}

int Timing::GetMinutesLeft(int timeRemainingInSec){
	return floor(timeRemainingInSec / 60);
}

int Timing::GetSecondsLeft(int timeRemainingInSec){
	return timeRemainingInSec % 60;
}

double Timing::GetTime() const{
#if _WIN32
	LARGE_INTEGER curTime, timeSinceStart;
	QueryPerformanceCounter(&curTime);

	timeSinceStart.QuadPart = curTime.QuadPart - sStartTime.QuadPart;

	return timeSinceStart.QuadPart * mPerfCountDuration;
#else
	auto now = high_resolution_clock::now();
	auto ms = duration_cast< milliseconds >(now - sStartTime).count();
	//a little uncool to then convert into a double just to go back, but oh well.
	return static_cast< double >(ms) / 1000;
#endif
}
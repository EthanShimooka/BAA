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
	//GAME TIMER LENGTH
	gameLengthInSeconds = playTimeLengthInSecs;
	minionCounter = 0;
	LARGE_INTEGER perfFreq;
	QueryPerformanceFrequency(&perfFreq);
	mPerfCountDuration = 1.0 / perfFreq.QuadPart;

	QueryPerformanceCounter(&sStartTime);

	mLastFrameStartTime = GetTime();

	attackCooldownLength = 2.0f;
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

// lobby timer
void Timing::SetLobbyCountdown(){
	gameLengthInSeconds = 3;
}

void Timing::SetTeamPickCountdown(){
	gameLengthInSeconds = 1;
}

void Timing::SetGamePlayCountdown(){
	gameLengthInSeconds = playTimeLengthInSecs;
}

void Timing::SetCountdownStart(){
	startTimeInSeconds = time(NULL);
	//std::cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@ Start Time(since epoch) = " << startTimeInSeconds << std::endl;
}

void Timing::StartAttackCooldown(){
	attackCooldown = time(NULL);
	attackCooldownRemains = clock();
}

int Timing::GetTimeRemainingS(){
	double timeRemaining = 0;
	time_t now = time(NULL);
	time_t timeElapsed = now - startTimeInSeconds;
	if (timeElapsed < 0 || NULL) return 0;
	//std::cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@ timeElapsed = " << timeElapsed << std::endl;
	//std::cout << "@@@@@@@@@@@@@@@@@ timeElapsed as int = " << (int)timeElapsed << std::endl;
	return gameLengthInSeconds - (int)timeElapsed;
}

string Timing::GetMinutesLeftAsString(int timeRemainingInSec){
	int min = (int)floor(timeRemainingInSec / 60);
	return std::to_string(min);
}

string Timing::GetSecondsLeftAsString(int timeRemainingInSec){
	int sec = timeRemainingInSec % 60;
	return std::to_string(sec);
}

bool Timing::AttackCooldownEnded(){
	time_t now = time(NULL);
	time_t timeElapsed = now - attackCooldown;
	//attackCooldown = time(NULL);
	if (timeElapsed >= attackCooldownLength) return true;
	else return false;
}

float Timing::GetAttackCooldownRemaining(){ 
	float timeElapsed = (((float)(clock() - attackCooldownRemains)) / CLOCKS_PER_SEC);
	//return ((attackCooldownLength - timeElapsed) < 0) ? 0 : (attackCooldownLength - timeElapsed); //THIS LINE ACTUALLY GIVES ATTACKCOOLDOWNREMAINING
	return ((timeElapsed < attackCooldownLength) ? timeElapsed : attackCooldownLength) / attackCooldownLength; //this line returns percentage of cooldown finishing. 1 is cooldown is completed, 0 is cooldown just started
}


bool Timing::SpawnMinions(){
	int timeLeft = GetTimeRemainingS();
	if (timeLeft >= gameLengthInSeconds - 4){ // Delay first wave
		return false;
	}
	if (timeLeft % 5 == 0 && minionCounter == 0){
		minionCounter = 1;
		//std::cout << "timeLeft = " << timeLeft << std::endl;
		return true;
	}
	else if (timeLeft % 5 == 4 && minionCounter == 1){
		minionCounter = 2;
		//std::cout << "timeLeft = " << timeLeft << std::endl;
		return true;
	}
	else if (timeLeft % 5 == 3 && minionCounter == 2){
		minionCounter = 3;
		//std::cout << "timeLeft = " << timeLeft << std::endl;
		return true;
	}
	else if (minionCounter == 3){
		minionCounter = 0;
		return false;
	}
	else{
		return false;
	}
}

void Timing::StartExplosionTimer(){
	explosionStart = clock();
}

bool Timing::ExplosionTimerEnded(){
	clock_t difference = clock() - explosionStart;
	unsigned aliveTime = difference / (CLOCKS_PER_SEC / 1000);
	if (aliveTime >= explosionLengthInMS) return true;
	else return false;
}

void Timing::SetQuailAbilityTimer(){
	quailAbilityStart = clock();
}

bool Timing::EndQuailAbilityTimer(){
	clock_t difference = clock() - quailAbilityStart;
	unsigned abilityTime = difference / (CLOCKS_PER_SEC / 1000);
	if (abilityTime >= quailAbilityLengthInMS){
		quailAbilityStart = 0;
		return true;
	}
	else return false;
}

void Timing::SetChickenAbilityTimer(){
	chickenAbilityStart = clock();
}

bool Timing::EndChickenAbilityTimer(){
	clock_t difference = clock() - chickenAbilityStart;
	unsigned abilityTime = difference / (CLOCKS_PER_SEC / 1000);
	if (abilityTime >= chickenAbilityLengthInMS){
		chickenAbilityStart = 0;
		return true;
	}
	else return false;
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
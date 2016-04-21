#include "Timer.h"


Timer::Timer(float length, void (*functionToCall))
{
	timerLength = (clock_t)length * 1000;
	func = functionToCall;

}


Timer::~Timer()
{

}

void Timer::Update(){
	if (timing){
		//InputManager* inputMan = InputManager::getInstance()->controller->rumble(strength 0-1,duration in millis);
		if ((startTime + timerLength) < (clock())) {
			timing = false;
			
		}
		else {
			//runs while timer is waiting to pop
		}
	}
}

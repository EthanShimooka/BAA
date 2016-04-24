#include "Invoke.h"

std::vector<Invoke*> Invoke::timers; //initializes timers to get rid of unresolved external error

Invoke::Invoke(float length, function_m functionToCall)
{
	timerLength = (clock_t)length * 1000;
	func = functionToCall;
	timers.push_back(this);
	timing = true;
	startTime = clock();
}


Invoke::~Invoke()
{
	auto it = std::find(timers.begin(), timers.end(), this);
	//finds timer in list of timers, moves it to the back then pops it off
	if (it != timers.end()) {
		using std::swap;
		swap(*it, timers.back());
		timers.pop_back();
	}
}

void Invoke::Update(){
	if (timing){
		if ((startTime + timerLength) < (clock())) {
			timing = false;
			func();
			delete(this);

		}
		else {
			//runs while timer is waiting to pop
		}
	}
}

void Invoke::UpdateTimers(){
	for (size_t i = 0; i < timers.size(); i++){
		timers[i]->Update();
	}
}
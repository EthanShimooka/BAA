#include "Invoke.h"


Invoke::Invoke(float length, void(*functionToCall))
{
	timerLength = (clock_t)length * 1000;
	func = &functionToCall;
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
			std::cout << "call function\n";
			this->~Invoke();

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
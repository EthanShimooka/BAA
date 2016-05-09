#include "Invoke.h"

std::vector<Invoke*> Invoke::timers; //initializes timers to get rid of unresolved external error

Invoke::Invoke(float length)
{
	timerLength = (clock_t)length * 1000;
	//func = functionToCall;
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

bool Invoke::isDone(){

	return !timing; //if this is timing, its not done. if its not timing, it should be done
}

void Invoke::Update(){
	if (timing){
		if ((startTime + timerLength) < (clock())) {
			timing = false;
			//func();
			//std::cout << "invoke timer!!!!!!!!!!!" << std::endl;
			//delete(this);

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

void Invoke::destroy(){
	delete(this);
}
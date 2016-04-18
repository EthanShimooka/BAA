#include "SystemUIObjectQueue.h"

SystemUIObjectQueue UIObjects;

SystemUIObjectQueue::SystemUIObjectQueue(){
}


SystemUIObjectQueue::~SystemUIObjectQueue(){
}



UIObject* SystemUIObjectQueue::AddObject(UIObject * obj){

	alive_objects.push_back(obj);
	return obj;
}

void SystemUIObjectQueue::DeleteObject(UIType g_id){

	for (unsigned int i = 0; i < alive_objects.size(); i++){
		if (alive_objects[i]->ID == g_id){
			//alive_objects.erase(std::remove(alive_objects.begin(), alive_objects.end(), alive_objects[i]), alive_objects.end());
		}
	}

}

void SystemUIObjectQueue::DeleteObjects(){
	for (unsigned int i = 0; i < alive_objects.size(); i++){
		delete alive_objects[i];
	}
	alive_objects.clear();
}
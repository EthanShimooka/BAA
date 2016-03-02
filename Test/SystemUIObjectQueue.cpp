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

void SystemUIObjectQueue::DeleteObject(int g_id){

	for (unsigned int i = 0; i < alive_objects.size(); i++){

		//if (alive_objects[i].ID == g_id)
	}

}
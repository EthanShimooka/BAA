#include "SystemGameObjectQueue.h"

SystemGameObjectQueue GameObjects;

SystemGameObjectQueue::SystemGameObjectQueue()
{
}


SystemGameObjectQueue::~SystemGameObjectQueue()
{
}




GameObject* SystemGameObjectQueue::AddObject(GameObject * obj){

	alive_objects.push_back(obj);
	return obj;
}

void SystemGameObjectQueue::DeleteObject(int g_id){

	for (unsigned int i = 0; i < alive_objects.size(); i++){

		//if (alive_objects[i].ID == g_id)
	}
	
}
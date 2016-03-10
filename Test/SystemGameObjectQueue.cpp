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

GameObject* SystemGameObjectQueue::GetGameObject(int g_id) {
	// iterate through alive objects 
	for (auto iter = alive_objects.begin(); iter != alive_objects.end(); ++iter) {
		if ((*iter)->ID == g_id) {
			return (*iter);
		}
	}
	// object not found
	return nullptr;
}
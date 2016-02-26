#include "SystemGameObjectQueue.h"


SystemGameObjectQueue::SystemGameObjectQueue()
{
}


SystemGameObjectQueue::~SystemGameObjectQueue()
{
}


void SystemGameObjectQueue::AddObject(GameObject * obj){

	alive_object.push_back(obj);

}

void SystemGameObjectQueue::DeleteObject(int g_id){

	for (int i = 0; i < alive_object.size(); i++){

		//if (alive_object[i].ID == g_id)
	}
	
}
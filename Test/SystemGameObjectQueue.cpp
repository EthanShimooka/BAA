#include "SystemGameObjectQueue.h"

SystemGameObjectQueue GameObjects;

SystemGameObjectQueue::SystemGameObjectQueue()
{
}


SystemGameObjectQueue::~SystemGameObjectQueue()
{
	std::cout << "--------------------------------" << std::endl;
	std::cout << "Alive Size: " << alive_objects.size() << std::endl;
	for (unsigned int i = 0; i < alive_objects.size(); i++){
		std::cout << "alive_object: " << alive_objects[i]->type << ": " << alive_objects[i]->ID << std::endl;
	}
	std::cout << "--------------------------------" << std::endl;
	for (unsigned int i = 0; i < alive_objects.size(); i++){
		std::cout << "alive " << i << std::endl;
		delete alive_objects[i];
	}
	for (unsigned int i = 0; i < dead_feathers.size(); i++){
		std::cout << "dead_f " << i << std::endl;
		delete dead_feathers[i];
	}
	for (unsigned int i = 0; i < dead_minions.size(); i++){
		std::cout << "dead_m " << i << std::endl;
		delete dead_minions[i];
	}
	for (unsigned int i = 0; i < dead_objects.size(); i++){
		std::cout << "dead_o " << i << std::endl;
		delete dead_objects[i];
	}

}

GameObject* SystemGameObjectQueue::AddObject(GameObject * obj){

	alive_objects.push_back(obj);
	std::cout << "pushed back: " << alive_objects.back()->type << ": " << alive_objects.back()->ID << std::endl;
	return obj;
}

void SystemGameObjectQueue::DeleteObject(uint64_t g_id){
	for (unsigned int i = 0; i < alive_objects.size(); i++){
		//if (alive_objects[i]->ID == g_id)
	}
}

//no longer used
void SystemGameObjectQueue::DeleteObjects(int g_id){
	//for (unsigned int i = 0; i < alive_objects.size(); i++){
	//	if (alive_objects[i]->ID == g_id){
	//		//GameObject::FreeComponents(alive_objects[i]);
	//		delete alive_objects[i];
	//	}
	//}
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
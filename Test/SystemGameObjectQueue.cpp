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
		std::cout << i + 1 << " alive_object: " << alive_objects[i]->type << ": " << alive_objects[i]->ID << "\t" << alive_objects[i] << std::endl;
	}
	std::cout << "--------------------------------" << std::endl;
	for (unsigned int i = 0; i < alive_objects.size(); i++){
		std::cout << "alive " << i << " " ;
		std::cout << alive_objects[i] << std::endl;
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
	//std::cout << "pushed back: " << alive_objects.back()->type << ": " << alive_objects.back()->ID << std::endl;
	return obj;
}

void SystemGameObjectQueue::DeleteObject(uint64_t g_id){
	for (unsigned int i = 0; i < alive_objects.size(); i++){
		if (alive_objects[i]->ID == g_id){
			delete alive_objects[i];
			alive_objects.erase(GameObjects.alive_objects.begin() + i);
			break;
		}
	}
}


void SystemGameObjectQueue::DeleteObjects(){
	while (!alive_objects.empty()){
		delete alive_objects.back();
		alive_objects.pop_back();
	}
}

GameObject* SystemGameObjectQueue::GetGameObject(uint64_t g_id) {
		// iterate through alive objects 
		for (auto iter = alive_objects.begin(); iter != alive_objects.end(); ++iter) {
		if ((*iter)->ID == g_id) {
			return (*iter);
			
		}
		
	}
	// object not found
		return nullptr;
} 
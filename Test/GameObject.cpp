#include "GameObject.h"
#include "AllComponentIncludes.h"


/// Constructor
GameObject::GameObject(){

	//component_count = 0;

	posX = 0.0;
	posY = 0.0;
	rotation = 0;
	scaleX = 1.0;
	scaleY = 1.0;
	flipH = false;
	flipV = false;
}

/// Constructor
GameObject::GameObject(float x, float y): posX(x), posY(y){
	//component_count = 0;
}

/// Destructor
GameObject::~GameObject(){
	/*std::cout << "calling gameobject destructor" << std::endl;
	while (!g_components.empty()){
		t_component currComp = g_components.back();
		delete &currComp;
	}
	std::cout << "end of gameobject destructor" << std::endl;*/
	
	//for (int i = 0; i < g_components.size(); i++){
	//	//if (type == OBJECT_PLAYER) {
	//		//if (g_components[i].type == COMPONENT_RENDER) {
	//		//	dynamic_cast<PlayerRenderCom
	//		//}
	//	//}
	//	if (g_components[i].type == 0){
	//		std::cout << g_components[i].type << std::endl;
	//	}
	//	delete g_components[i].component;
	//}
	LogManager* log = LogManager::GetLogManager();
	log->logBuffer << type << std::endl;
	log->flush();
	switch (type){
	case OBJECT_PLAYER :
		for (unsigned int i = 0; i < g_components.size(); i++) {
			switch (g_components[i].type) {
			case COMPONENT_RENDER:
				delete dynamic_cast<PlayerRenderComponent*>(g_components[i].component);
				break;
			case COMPONENT_LOGIC:
				delete dynamic_cast<PlayerLogicComponent*>(g_components[i].component);
				break;
			case COMPONENT_PHYSICS:
				delete dynamic_cast<PlayerPhysicsComponent*>(g_components[i].component);
				break;
			case COMPONENT_INPUT:
				delete dynamic_cast<PlayerInputComponent*>(g_components[i].component);
				break;
			case COMPONENT_NETWORK:
				delete dynamic_cast<PlayerNetworkComponent*>(g_components[i].component);
				break;
			case COMPONENT_CLASS:
				delete dynamic_cast<ClassComponent*>(g_components[i].component);
			default:
				break;
			}
		}
		break;
	case OBJECT_FEATHER:
		for (unsigned int i = 0; i < g_components.size(); i++) {
			switch (g_components[i].type) {
			case COMPONENT_RENDER:
				delete dynamic_cast<FeatherRenderComponent*>(g_components[i].component);
				break;
			case COMPONENT_LOGIC:
				delete dynamic_cast<FeatherLogicComponent*>(g_components[i].component);
				break;
			case COMPONENT_PHYSICS:
				delete dynamic_cast<FeatherPhysicsComponent*>(g_components[i].component);
				break;
			case COMPONENT_NETWORK:
				delete dynamic_cast<FeatherNetworkComponent*>(g_components[i].component);
				break;
			default:
				break;
			}
		}
		break;
	case OBJECT_MINION:
		for (unsigned int i = 0; i < g_components.size(); i++) {
			switch (g_components[i].type) {
			case COMPONENT_RENDER:
				delete dynamic_cast<MinionRenderComponent*>(g_components[i].component);
				break;
			case COMPONENT_LOGIC:
				delete dynamic_cast<MinionLogicComponent*>(g_components[i].component);
				break;
			case COMPONENT_PHYSICS:
				delete dynamic_cast<MinionPhysicsComponent*>(g_components[i].component);
				break;
			case COMPONENT_NETWORK:
				delete dynamic_cast<MinionNetworkComponent*>(g_components[i].component);
				break;
			default:
				break;
			}
		}
		break;
	case OBJECT_PLATFORM:
		for (unsigned int i = 0; i < g_components.size(); i++) {
			switch (g_components[i].type) {
			case COMPONENT_RENDER:
				delete dynamic_cast<PlatformRenderComponent*>(g_components[i].component);
				break;
			case COMPONENT_PHYSICS:
				delete dynamic_cast<PlatformPhysicsComponent*>(g_components[i].component);
				break;
			default:
				break;
			}
		}
		break;
	case OBJECT_POWERSHIELD:
		for (unsigned int i = 0; i < g_components.size(); i++) {
			switch (g_components[i].type) {
			case COMPONENT_RENDER:
				delete dynamic_cast<PowerShieldRenderComponent*>(g_components[i].component);
				break;
			case COMPONENT_LOGIC:
				delete dynamic_cast<PowerShieldLogicComponent*>(g_components[i].component);
				break;
			case COMPONENT_PHYSICS:
				delete dynamic_cast<PowerShieldPhysicsComponent*>(g_components[i].component);
				break;
			case COMPONENT_NETWORK:
				delete dynamic_cast<PowerShieldNetworkComponent*>(g_components[i].component);
				break;
			default:
				break;
			}
		}
		break;
	default :
		break;
	}
}

void GameObject::setPos(float x, float y){
	posX = x;
	posY = y;
	
}

void GameObject::AddComponent(int c_type, Component* comp){
	
	t_component tcomp;

	/// Allocation into t_component struct
	tcomp.type = c_type;
	tcomp.component = comp;
	/// Push back onto GameObjects struct
	g_components.push_back(tcomp);
	/// Add number of total components
	//component_count++;
	
}


void GameObject::UpdateComponents(){

	for (unsigned int i = 0; i < g_components.size(); i++){
		g_components[i].component->Update();
	}
}

void GameObject::UpdateComponentByType(int c_type){

	for (unsigned int i = 0; i < g_components.size(); i++){
	
		if (g_components[i].type == c_type)
			g_components[i].component->Update();
	}	
}

Component* GameObject::GetComponent(int c_type) {
	for (unsigned int i = 0; i < g_components.size(); i++){
		if (g_components[i].type == c_type)
			return g_components[i].component;
	}
	return nullptr;
}
#include "GameObject.h"
#include "AllComponentIncludes.h"


/// Constructor
GameObject::GameObject(){

	//component_count = 0;

	//posX = 0.0;
	//posY = 0.0;
	isLocal = false;
	rotation = 0;
	scaleX = 1.0;
	scaleY = 1.0;
	flipH = false;
	flipV = false;
	ID = -1;
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

	for (unsigned int i = 0; i < g_components.size(); i++) {
		delete g_components[i].component;
	}

	/*for (unsigned int i = 0; i < g_components.size(); i++) {
		switch (g_components[i].type) {
			case COMPONENT_RENDER:
				delete dynamic_cast<RenderComponent*>(g_components[i].component);
				break;
			case COMPONENT_LOGIC:
				delete dynamic_cast<LogicComponent*>(g_components[i].component);
				break;
			case COMPONENT_PHYSICS:
				delete dynamic_cast<PhysicsComponent*>(g_components[i].component);
				break;
			case COMPONENT_INPUT:
				delete dynamic_cast<InputComponent*>(g_components[i].component);
				break;
			case COMPONENT_NETWORK:
				delete dynamic_cast<NetworkComponent*>(g_components[i].component);
				break;
			case COMPONENT_CLASS:
				delete dynamic_cast<ClassComponent*>(g_components[i].component);
				break;
			case COMPONENT_UI:
				delete dynamic_cast<UIComponent*>(g_components[i].component);
				break;
			default:
				break;
		}
	}*/


<<<<<<< HEAD
=======
	case OBJECT_BOOMERANG:
		for (unsigned int i = 0; i < g_components.size(); i++) {
			switch (g_components[i].type) {
			case COMPONENT_RENDER:
				delete dynamic_cast<BoomerangRenderComponent*>(g_components[i].component);
				break;
			case COMPONENT_LOGIC:
				delete dynamic_cast<BoomerangLogicComponent*>(g_components[i].component);
				break;
			case COMPONENT_PHYSICS:
				delete dynamic_cast<BoomerangPhysicsComponent*>(g_components[i].component);
				break;
			default:
				break;
			}
		}
		break;
	case OBJECT_MINE:
		for (unsigned int i = 0; i < g_components.size(); i++) {
			switch (g_components[i].type) {
			case COMPONENT_RENDER:
				delete dynamic_cast<MineRenderComponent*>(g_components[i].component);
				break;
			case COMPONENT_LOGIC:
				delete dynamic_cast<MineLogicComponent*>(g_components[i].component);
				break;
			case COMPONENT_PHYSICS:
				delete dynamic_cast<MinePhysicsComponent*>(g_components[i].component);
				break;
			default:
				break;
			}
		}
		break;
	case OBJECT_LAUNCHER:
		for (unsigned int i = 0; i < g_components.size(); i++) {
			switch (g_components[i].type) {
			case COMPONENT_RENDER:
				delete dynamic_cast<LauncherRenderComponent*>(g_components[i].component);
				break;
			case COMPONENT_LOGIC:
				delete dynamic_cast<LauncherLogicComponent*>(g_components[i].component);
				break;
			case COMPONENT_PHYSICS:
				delete dynamic_cast<LauncherPhysicsComponent*>(g_components[i].component);
				break;
			default:
				break;
			}
		}
		break;
	case OBJECT_PARTICLE:
		for (unsigned int i = 0; i < g_components.size(); i++) {
			switch (g_components[i].type) {
			case COMPONENT_RENDER:
				delete dynamic_cast<RenderComponent*>(g_components[i].component);
				break;
			default:
				break;
			}
		}
		break;
	default :
		std::cout << "NEED TO ADD DECONSTRUCTOR FOR OBJECT TYPE: " << type << std::endl;
		break;
	}
>>>>>>> refs/remotes/origin/master
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
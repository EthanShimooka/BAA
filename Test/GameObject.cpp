#include "GameObject.h"

/// Constructor
GameObject::GameObject(){

	component_count = 0;

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

	component_count = 0;

}

/// Destructor
GameObject::~GameObject(){
	/*std::cout << "calling gameobject destructor" << std::endl;
	while (!g_components.empty()){
		t_component currComp = g_components.back();
		delete &currComp;
	}
	std::cout << "end of gameobject destructor" << std::endl;*/
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
	component_count++;
	
}


void GameObject::UpdateComponents(){

	for (int i = 0; i < component_count; i++){
		g_components[i].component->Update();
	}
}

void GameObject::UpdateComponentByType(int c_type){

	for (int i = 0; i < component_count; i++){
	
		if (g_components[i].type == c_type)
			g_components[i].component->Update();
	}	
}

Component* GameObject::GetComponent(int c_type) {
	for (int i = 0; i < component_count; i++){
		if (g_components[i].type == c_type)
			return g_components[i].component;
	}
	return nullptr;
}

void GameObject::FreeComponents(GameObject* toFree){
	for (int i = 0; i < toFree->g_components.size(); i++){
		delete toFree->g_components[i].component;
	}
}
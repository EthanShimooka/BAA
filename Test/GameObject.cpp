#include "GameObject.h"

/// Constructor
GameObject::GameObject(){

	component_count = 0;

}

/// Destructor
GameObject::~GameObject(){}


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
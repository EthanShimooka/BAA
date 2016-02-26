#include "GameObject.h"


GameObject::GameObject(){

	component_count = 0;

}

GameObject::~GameObject(){}

void GameObject::AddComponent(int c_type, Component* comp){

	
	t_component tcomp;

	tcomp.type = c_type;
	tcomp.component = comp;

	g_components.push_back(tcomp);
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
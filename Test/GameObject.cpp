#include "GameObject.h"


GameObject::GameObject(){

	component_count = 0;

}

GameObject::~GameObject(){}

void GameObject::AddComponent(Component* comp){

	g_components.push_back(comp);

}


void GameObject::UpdateComponents(){

	for (int i = 0; i <= component_count; i++){
		g_components[i]->Update();
	}

}
#include "UIObject.h"

/// Constructor
UIObject::UIObject(){

	component_count = 0;

}

/// Constructor
UIObject::UIObject(float x, float y) : posX(x), posY(y){

	component_count = 0;

}

/// Destructor
UIObject::~UIObject(){}


void UIObject::setPos(float x, float y){
	posX = x;
	posY = y;
}

void UIObject::AddComponent(int c_type, Component* comp){

	uiT_component tcomp;

	/// Allocation into t_component struct
	tcomp.type = c_type;
	tcomp.component = comp;
	/// Push back onto GameObjects struct
	g_components.push_back(tcomp);
	/// Add number of total components
	component_count++;

}


void UIObject::UpdateComponents(){

	for (int i = 0; i < component_count; i++){
		g_components[i].component->Update();
	}
}

void UIObject::UpdateComponentByType(int c_type){

	for (int i = 0; i < component_count; i++){

		if (g_components[i].type == c_type)
			g_components[i].component->Update();
	}
}

Component* UIObject::GetComponent(int c_type) {
	for (int i = 0; i < component_count; i++){
		if (g_components[i].type == c_type)
			return g_components[i].component;
	}
	return nullptr;
}
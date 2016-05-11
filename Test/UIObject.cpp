#include "UIObject.h"
#include "UIComponentIncludes.h"

/// Constructor
UIObject::UIObject() : posX(0), posY(0), rotation(0), scale(1){

	visible = true;
	component_count = 0;

}

/// Constructor
UIObject::UIObject(float x, float y, float r, float s) : 
				   posX(x), posY(y), rotation(r), scale(s){
	visible = true;
	component_count = 0;

}

/// Destructor
UIObject::~UIObject(){
	for (unsigned int i = 0; i < g_components.size(); i++) {
		switch (g_components[i].type){
		case COMPONENT_RENDER:
			delete dynamic_cast<UIRenderComponent*>(g_components[i].component);
			break;
		case COMPONENT_INPUT:
			delete dynamic_cast<UIInputComponent*>(g_components[i].component);
			break;
		case COMPONENT_UI:
			delete dynamic_cast<UIComponent*>(g_components[i].component);
			break;
		}
	}
}


void UIObject::setPos(float x, float y){
	posX = x;
	posY = y;
}

void UIObject::setRotation(float r){
	rotation = r;
}

void UIObject::setScale(float s){
	scale = s;
}

void UIObject::AddComponent(int c_type, Component* comp){

	uiT_component tcomp;

	/// Allocation into t_component struct
	tcomp.type = c_type;
	tcomp.component = comp;
	/// Push back onto UIObjects struct
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

void UIObject::DetachComponent(){
	for (int i = 0; i < component_count; i++){
		delete g_components[i].component;
		component_count--;
	}
}

void UIObject::setWidthAndHeight(int w, int h){
	this->width = w;
	this->height = h;
}

int UIObject::getWidth(){
	return this->width;
}

int UIObject::getHeight(){
	return this->width;
}

#pragma once
#ifndef UICOMPONENT_H_INCLUDED
#define UICOMPONENT_H_INCLUDED

#include <vector>
#include "Component.h"
#include "UIObject.h"
#include "include\InputManager.h"
#include "include\network\NetIncludes.h"

class UIComponent : public Component
{
public:
	UIComponent();
	~UIComponent();

	/// UIObject Container Reference
	UIObject* uiObjectRef;


	/// Virtual Update function
	virtual void Update();
};

#endif
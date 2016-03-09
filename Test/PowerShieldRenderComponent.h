/**
*  PowerShieldRenderComponent.h
*  Authors: Ethan Shimooka
*  Date 3/4/2016
*  Description :
Render Component for Class Object "Shield".

*/

#ifndef POWERSHIELDRENDERCOMPONENTCOMPONENT_H_INCLUDED
#define POWERSHIELDRENDERCOMPONENTCOMPONENT_H_INCLUDED

#pragma once
#include "LogicComponent.h"
#include "PowerShieldIncludes.h"
#include "GameObject.h"
#include "RenderComponent.h"

class PowerShieldRenderComponent : public RenderComponent
{
public:
	/// Constructor
	PowerShieldRenderComponent(GameObject* shield);
	/// Deconstrucor
	~PowerShieldRenderComponent();
	/// Update Function
	void Update();

};

#endif
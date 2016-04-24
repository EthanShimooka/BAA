/**
*  MidPlatShieldRenderComponet.h
*  Authors: Ethan Shimooka
*  Date 3/31/2016
*  Description :
Render Component class for the midPlatform

*/
#pragma once
#ifndef MIDPLATSHIELDRENDERCOMPONENT_H_INCLUDED
#define MIDPLATSHIELDRENDERCOMPONENT_H_INCLUDED


#include "RenderComponent.h"
#include "MidPlatShieldComponentIncludes.h"

class MidPlatShieldRenderComponent :
	public RenderComponent
{
public:
	MidPlatShieldRenderComponent(GameObject* platform);
	~MidPlatShieldRenderComponent();
	/// Void Update function

	void Update();
};

#endif


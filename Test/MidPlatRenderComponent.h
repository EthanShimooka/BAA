/**
*  MidPlatRenderComponet.h
*  Authors: Ethan Shimooka
*  Date 3/31/2016
*  Description :
Render Component class for the midPlatform

*/

#pragma once
#ifndef MIDPLATRENDERCOMPONENT_H_INCLUDED
#define MIDPLATRENDERCOMPONENT_H_INCLUDED

#include "RenderComponent.h"
#include "MidPlatComponentIncludes.h"


class MidPlatRenderComponent :
	public RenderComponent
{
public:
	/// Constructor
	MidPlatRenderComponent(GameObject* platform);
	/// Deconstructor
	~MidPlatRenderComponent();
};

#endif
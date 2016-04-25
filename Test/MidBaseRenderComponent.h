/**
*  MidBaseRenderComponet.h
*  Authors: Ethan Shimooka
*  Date 3/31/2016
*  Description :
Render Component class for the midBase
*/

#pragma once

#ifndef MIDBASERENDERCOMPONENT_H_INCLUDED
#define MIDBASERENDERCOMPONENT_H_INCLUDED




#include "RenderComponent.h"
class MidBaseRenderComponent :
	public RenderComponent
{
public:
	void buildBody(int team);
	void buildAnimations();
	MidBaseRenderComponent(GameObject * base,int team = TEAM_YELLOW);
	~MidBaseRenderComponent();

	void Update();

};

#endif
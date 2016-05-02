#pragma once

/**
*  MidBaseRenderComponet.h
*  Authors: Ethan Shimooka
*  Date 5/1/2016
*  Description :
Render Component class for the Well
*/

#pragma once

#ifndef WELLRENDERCOMPONENT_H_INCLUDED
#define WELLRENDERCOMPONENT_H_INCLUDED




#include "RenderComponent.h"
class WellRenderComponent :
	public RenderComponent
{
public:
	WellRenderComponent(GameObject * well, int team);
	~WellRenderComponent();
	void Update();
};

#endif
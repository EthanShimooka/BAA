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
	MidBaseRenderComponent(GameObject * base);
	~MidBaseRenderComponent();

	void Update();

};

#endif
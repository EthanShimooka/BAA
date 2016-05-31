/**
*  MidBirdRenderComponet.h
*  Authors: Ethan Shimooka
*  Date 5/26/2016
*  Description :
	Render Component for middle score Bird.
*/

#pragma once
#ifndef MIDBIRDRENDERCOMPONENT_H_INCLUDED
#define MIDBIRDRENDERCOMPONENT_H_INCLUDED

#include "RenderComponent.h"
#include "include\SceneManager.h"
#include "Stats.h"

#include "RenderComponent.h"
class MidBirdRenderComponent :
	public RenderComponent
{
public:
	MidBirdRenderComponent(GameObject * bird);
	~MidBirdRenderComponent();
	void buildAnimation();
	void animationLogic();
	void Update();
	bool idleToggle = false;
	int flagUp = 0;


};

#endif
/**
*  LauncherPhysicsComponet.h
*  Authors: Ethan Shimooka
*  Date 5/1/2016
*  Description :
Physics Component class for the Launcher
*/

#pragma once

#ifndef LAUNCHERPHYSICSCOMPONENT_H_INCLUDED
#define LAUNCHERPHYSICSCOMPONENT_H_INCLUDED



#include "PhysicsComponent.h"
class LauncherPhysicsComponent :
	public PhysicsComponent
{
public:
	LauncherPhysicsComponent(GameObject* launcher);
	~LauncherPhysicsComponent();
	void init(float size);
	void handleCollision(GameObject* otherObj);
	void Update();
};

#endif
/**
*  LauncherRenderComponet.h
*  Authors: Ethan Shimooka
*  Date 5/1/2016
*  Description :
Render Component class for the Launcher
*/

#pragma once

#ifndef LAUNCHERRENDERCOMPONENT_H_INCLUDED
#define LAUNCHERRENDERCOMPONENT_H_INCLUDED



#include "RenderComponent.h"
class LauncherRenderComponent :
	public RenderComponent
{
public:
	LauncherRenderComponent(GameObject * launcher, int team);
	~LauncherRenderComponent();
	void Update();
	void buildAnimation();
};

#endif
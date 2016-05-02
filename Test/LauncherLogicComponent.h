/**
*  LogicRenderComponent.h
*  Authors: Ethan Shimooka
*  Date 5/1/2016
*  Description :
Logic Component class for the Launcher
*/
#pragma once
#ifndef LAUNCHERLOGICCOMPONENT_H_INCLUDED
#define LAUNCHERLOGICCOMPONENT_H_INCLUDED

#include "LogicComponent.h"
class LauncherLogicComponent :
	public LogicComponent
{
public:
	LauncherLogicComponent(GameObject * launcher);
	~LauncherLogicComponent();
	void showButton();
	void triggerButton();
	void Update();
};

#endif
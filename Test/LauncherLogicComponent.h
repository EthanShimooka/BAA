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
#include "LauncherComponentIncludes.h"

class LauncherLogicComponent :
	public LogicComponent
{
public:
	LauncherLogicComponent(GameObject * launcher);
	~LauncherLogicComponent();

	bool launchable = false;

	void showButton();
	void triggerButton();
	void hideButton();
	void Update();

	clock_t timeSinceToggle;
	//clock_t timeSinceFuseLit;
	clock_t clockDiff;

};

#endif
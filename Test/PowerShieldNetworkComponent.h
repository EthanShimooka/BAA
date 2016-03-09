/**
*  PowerShieldNetworkComponent.h
*  Authors: Ethan Shimooka
*  Date 3/4/2016
*  Description :
Network Component for Class Object "Shield".

*/

#ifndef POWERSHIELDNETWORKCOMPONENTCOMPONENT_H_INCLUDED
#define POWERSHIELDNETWORKCOMPONENTCOMPONENT_H_INCLUDED

#pragma once
#include "LogicComponent.h"
#include "PowerShieldIncludes.h"
#include "GameObject.h"
#include "RenderComponent.h"
#include "NetworkComponent.h"

class PowerShieldNetworkComponent :  public NetworkComponent
{
public:

	/// Constructor
	PowerShieldNetworkComponent(GameObject* shield);
	/// Destructor
	~PowerShieldNetworkComponent();
	/// Update function
	void Update();

};

#endif
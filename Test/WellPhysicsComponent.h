#pragma once

/**
*  WellPhysicsComponet.h
*  Authors: Ethan Shimooka
*  Date 5/1/2016
*  Description :
Physics Component class for the Well
*/

#pragma once

#ifndef WELLPHYSICSCOMPONENT_H_INCLUDED
#define WELLPHYSICSCOMPONENT_H_INCLUDED



#pragma once
#include "PhysicsComponent.h"
class WellPhysicsComponent :
	public PhysicsComponent
{
public:
	WellPhysicsComponent();
	~WellPhysicsComponent();
};

#endif
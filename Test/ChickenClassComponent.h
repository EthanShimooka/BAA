#pragma once
#ifndef CHICKENCLASSCOMPONENT_H_INCLUDED
#define CHICKENCLASSCOMPONENT_H_INCLUDED

#include "ClassComponent.h"
#include "PowerShieldObjectFactory.h"
class ChickenClassComponent :
	public ClassComponent
{
public:
	ChickenClassComponent(GameObject* player);
	~ChickenClassComponent();
	void Update();
	int useAbility();
	static void animation(SDLRenderObject** objRef, map_obj& allObjs, map_anim& animations);
};

#endif
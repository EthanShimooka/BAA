#pragma once
#ifndef QUAILCLASSCOMPONENT_H_INCLUDED
#define QUAILCLASSCOMPONENT_H_INCLUDED

#include "ClassComponent.h"
#include "PlayerObjectFactory.h"
class QuailClassComponent :
	public ClassComponent
{
public:
	QuailClassComponent(GameObject* player);
	~QuailClassComponent();
	void Update();
	int useAbility();
	static void animation(SDLRenderObject** objRef, map_obj& allObjs, map_anim& animations);
	int getClass();
};

#endif
#pragma once
#ifndef FLAMINGOCLASSCOMPONENT_H_INCLUDED
#define FLAMINGOCLASSCOMPONENT_H_INCLUDED

#include "ClassComponent.h"
#include "MineObjectFactory.h"
#include "PlayerObjectFactory.h"

class FlamingoClassComponent :
	public ClassComponent
{
public:
	FlamingoClassComponent(GameObject* player);
	~FlamingoClassComponent();
	void Update();
	int useAbility();
	static void animation(SDLRenderObject** objRef, map_obj& allObjs, map_anim& animations);
	int getClass();
};

#endif
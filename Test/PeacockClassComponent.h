#pragma once
#include "ClassComponent.h"
class PeacockClassComponent :
	public ClassComponent
{
public:
	PeacockClassComponent(GameObject* player);
	~PeacockClassComponent();
	void Update();
	int useAbility();
	static void animation(SDLRenderObject** objRef, map_obj& allObjs, map_anim& animations);
};


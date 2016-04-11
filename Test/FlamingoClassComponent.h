#pragma once
#include "ClassComponent.h"
class FlamingoClassComponent :
	public ClassComponent
{
public:
	FlamingoClassComponent(GameObject* player);
	~FlamingoClassComponent();
	void Update();
	bool UseAbility();
	static void animation(SDLRenderObject** objRef, map_obj& allObjs, map_anim& animations);
};


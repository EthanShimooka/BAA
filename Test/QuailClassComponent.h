#pragma once
#include "ClassComponent.h"
class QuailClassComponent :
	public ClassComponent
{
public:
	QuailClassComponent(GameObject* player);
	~QuailClassComponent();
	void Update();
	int useAbility();
	static void animation(SDLRenderObject** objRef, map_obj& allObjs, map_anim& animations);
};


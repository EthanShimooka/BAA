#pragma once
#include "ClassComponent.h"
class TurkeyClassComponent :
	public ClassComponent
{
public:
	TurkeyClassComponent(GameObject* player);
	~TurkeyClassComponent();
	void Update();
	bool UseAbility();
	static void animation(SDLRenderObject** objRef, map_obj& allObjs, map_anim& animations);
};


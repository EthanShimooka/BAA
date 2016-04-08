#pragma once
#include "ClassComponent.h"
class ChickenClassComponent :
	public ClassComponent
{
public:
	ChickenClassComponent(GameObject* player);
	~ChickenClassComponent();
	void Update();
	bool UseAbility();

};


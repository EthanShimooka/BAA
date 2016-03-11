#pragma once
#ifndef FEATHERLOGICCOMPONENT_H_INCLUDED
#define FEATHERLOGICCOMPONENT_H_INCLUDED

#include "LogicComponent.h"
#include "FeatherComponentIncludes.h"

class FeatherLogicComponent : public LogicComponent
{
public:
	/// Constructor
	FeatherLogicComponent(GameObject* feather, float posX, float posY, float dx, float dy);
	/// Destructor
	~FeatherLogicComponent();
	/// Update Function
	void Update();
	/// init Function
	void init(float posX, float posY, float dx, float dy);

	float x;
	float y;

	// reference to player gameObject
	GameObject* owner;
	void setOwner(GameObject* ref);

	/// give birdseed to player function
	void giveBirdseed(int seeds);
};

#endif
#pragma once
#ifndef FEATHERLOGICCOMPONENT_H_INCLUDED
#define FEATHERLOGICCOMPONENT_H_INCLUDED

#include "LogicComponent.h"
#include "FeatherComponentIncludes.h"

class FeatherLogicComponent : public LogicComponent
{
public:
	/// This is a reference to the player that spawned it
	GameObject* owner;
	/// Constructor
	FeatherLogicComponent(GameObject* feather);
	/// Destructor
	~FeatherLogicComponent();
	/// Update Function
	void Update();
	/// init Function
	void init();
	///Refactored method to increment the birds seed count
	void giveBirdseed(int numSeeds);
	/// Plays feather sound effect if feather is onscreen for local simulation
	void playSound();
	/// Indicates whether sfx for this object has already been played
	bool soundPlayed = false;
};

#endif
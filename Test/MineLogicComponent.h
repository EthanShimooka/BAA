#pragma once
#ifndef MINELOGICCOMPONENT_H_INCLUDED
#define MINELOGICCOMPONENT_H_INCLUDED
#include "LogicComponent.h"
#include "MineComponentIncludes.h"
class MineLogicComponent : public LogicComponent
{
public:
	/// Constructor
	MineLogicComponent(GameObject* player);
	/// Destructor
	~MineLogicComponent();
	/// Update Function
	void Update();
	/// Signals the 1 second delay before exploding
	void lightFuse();
	/// Destroys mine object
	void detonateMine();
	/// Detonates the mine if it's been alive longer than 20 seconds
	void checkTimer();
	//Refactored method to increment the birds seed count
	void giveBirdseed(int numSeeds);
	/// Plays mine sound effect if mine is onscreen for local simulation
	void playSound();
	/// Indicates whether sfx for this object has already been played
	bool soundPlayed = false;
	/// This is a reference to the player that spawned it
	GameObject* owner;
	bool fuseLit = false;
	int blownUp = 0;
	clock_t timeSinceBirth;
	clock_t timeSinceFuseLit;

private:
	/// Signals the blow up sequence to start. Once sequence finishes, either
	/// destroy the object or send it to the object pool. Entites should only
	/// be able to trip the fuse, but not directly call this function. Only itself can.
	void blowUp();
	unsigned int mineLength = 20000;
};
#endif

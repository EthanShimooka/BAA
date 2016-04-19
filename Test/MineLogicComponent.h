#pragma once
#ifndef MINELOGICCOMPONENT_H_INCLUDED
#define MINELOGICCOMPONENT_H_INCLUDED
#include "LogicComponent.h"
#include "MineComponentIncludes.h"
class MineLogicComponent :
	public LogicComponent
{
public:
	/// Constructor
	MineLogicComponent(GameObject* player);
	/// Destructor
	~MineLogicComponent();
	/// Update Function
	void Update();
	/// Signals the blow up sequence to start. Once sequence finishes, either
	/// destroy the object or send it to the object pool
	void blowUp();
	/// Signals the 1 second delay before exploding
	void lightFuse();

	GameObject* spawner;
	bool fuseLit = false;
	int blownUp = 0;
	clock_t timeSinceBirth;
	clock_t timeSinceFuseLit;
};
#endif

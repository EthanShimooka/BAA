#pragma once
#include "LogicComponent.h"
#ifndef MINELOGICCOMPONENT_H_INCLUDED
#define MINELOGICCOMPONENT_H_INCLUDED
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
};
#endif

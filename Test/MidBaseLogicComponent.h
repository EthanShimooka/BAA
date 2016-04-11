#pragma once
#ifndef MIDBASELOGICCOMPONENT_H_INCLUDED
#define MIDBASELOGICCOMPONENT_H_INCLUDED

#include "LogicComponent.h"



class MidBaseLogicComponent :
	public LogicComponent
{
public:
	int base_health = 5;


	MidBaseLogicComponent(GameObject * base);
	~MidBaseLogicComponent();

	void Update();
	//void health();
	void attacked();

	
};

#endif

#pragma once
#ifndef COMPONENT_H_INCLUDED
#define COMPONENT_H_INCLUDED


typedef enum {
	COMPONENT_RENDER = 0,
	COMPONENT_INPUT = 1,
	COMPONENT_NETWORK = 2,
	COMPONENT_MOVEMENT = 3,
	COMPONENT_PHYSICS = 4,
}COMPONENT_TYPE;


class Component
{
public:
	Component();
	~Component();




	/// Component Initialazation
//	virtual void Init();	
	
	/// Component Update
	virtual void Update();

	/// Component Termination
//	virtual void Shutdown();

	/// Message Handling System Function *may Not Need*
//	virtual void HandleMsg();


};

#endif
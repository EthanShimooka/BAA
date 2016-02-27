/**
*  Component.h
*  Authors: Ethan Shimooka
*  Date 2/25/2016
*  Description :
	Component represents the abstreact base class from which all other
	Components are derived. This file also contains the typedef enumerations
	for component types.

*/

#pragma once
#ifndef COMPONENT_H_INCLUDED
#define COMPONENT_H_INCLUDED


/// Enumerations of Component types.
/// ***LIST INCOMPLETE*** 

typedef enum {
	COMPONENT_RENDER = 0,
	COMPONENT_INPUT = 1,
	COMPONENT_NETWORK = 2,
	COMPONENT_MOVEMENT = 3,
	COMPONENT_PHYSICS = 4,
	COMPONENT_LOGIC = 5,
}COMPONENT_TYPE;


class Component
{
public:
	/// Constructor
	Component();
	/// Destructor
	~Component();



	/// Component Update
	virtual void Update();


	// TODO:

	/// Component Initialazation
	//	virtual void Init();	

	/// Component Termination
//	virtual void Shutdown();

	/// Message Handling System Function *may Not Need*
//	virtual void HandleMsg();


};

#endif
#pragma once
#ifndef COMPONENT_H_INCLUDED
#define COMPONENT_H_INCLUDED


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
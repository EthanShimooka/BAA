/**
*  NetworkComponent.h
*  Authors: Ethan Shimooka
*  Date 2/26/2016
*  Description :
	NetworkComponent represents the abstract base class from which 
	all other network components a are derived from. Should be overriden
	with object type specific component

*/

#pragma once
#ifndef NETWORKCOMPONENT_H_INCLUDED
#define NETWORKCOMPONENT_H_INCLUDED


//#include "Component.h"
#include "GameObject.h"
#include "include\network\NetIncludes.h"


class NetworkComponent :	public Component
{
public:
	NetworkComponent();
	virtual ~NetworkComponent();

	/// GameObject Container Refrence. (Assigned upon GameObject Creation) 
	GameObject* gameObjectRef;
	uint32_t sequence = 0;
	clock_t	lastTimeSent;
	int interval;
	

	/// update object Positions from Input
	virtual void Update();
	bool canSend();

	queue<OutputMemoryBitStream*> outgoingPackets;
	queue<InputMemoryBitStream> incomingPackets;
};

#endif
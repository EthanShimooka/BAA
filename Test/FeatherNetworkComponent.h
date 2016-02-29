#pragma once
#ifndef FEATHERNETWORKCOMPONENT_H_INCLUDED
#define FEATHERNETWORKCOMPONENT_H_INCLUDED
#include "NetworkComponent.h"
#include "FeatherComponentIncludes.h"

class FeatherNetworkComponent : public NetworkComponent
{
private:
public:
	/// Construcor 
	FeatherNetworkComponent();
	/// Destructor
	~FeatherNetworkComponent();
	/// Update
	void Update();
};

#endif
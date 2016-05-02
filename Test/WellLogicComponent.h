#pragma once

/**
*  WellLogicComponet.h
*  Authors: Ethan Shimooka
*  Date 5/1/2016
*  Description :
Logic Component class for the Well
*/

#pragma once

#ifndef WELLLOGICCOMPONENT_H_INCLUDED
#define WELLLOGICCOMPONENT_H_INCLUDED


#include "LogicComponent.h"
class WellLogicComponent :
	public LogicComponent
{
public:
	WellLogicComponent();
	~WellLogicComponent();
};

#endif
/**
*  PlayerRenderComponet.h
*  Authors: Ethan Shimooka
*  Date 2/25/2016
*  Description :
PlayerRenderComponent represents the Player-specific Render class 

*/

#pragma once
#ifndef PLAYERRENDERCOMPONENT_H_INCLUDED
#define PLAYERRENDERCOMPONENT_H_INCLUDED
#include "RenderComponent.h"
#include "include\SceneManager.h"

class PlayerRenderComponent : public RenderComponent
{
public:
	/// Constructor
	PlayerRenderComponent();
	/// Destructor
	~PlayerRenderComponent();
	/// Update
	void Update();
};

#endif
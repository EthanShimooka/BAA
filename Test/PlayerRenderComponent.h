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
#include "PlayerComponentIncludes.h"
#include "ChargeParticle.h"
#include "UIRenderComponent.h"

using function_t = void(*)(SDLRenderObject**, map_obj&, map_anim&);

class PlayerRenderComponent : public RenderComponent
{
public:
	/// Constructor
	PlayerRenderComponent(GameObject* player, function_t func);
	/// Destructor
	~PlayerRenderComponent();
	/// render various physics
	void RenderPhysics();
	/// Update
	void Update();
	/// variable that decides where to aim
	float aimRotation;
	void setAnimation(std::string name);
	void setNextAnimation(std::string name);
	/// Reference to the crosshair UIObject's image
	SDLRenderObject* crosshairRef;
	//ChargeParticle * charger;
	//UIRenderComponent* crosshairObjRef;
	// Reference to charge bar that follows player
	//SDLRenderObject* chargebarMeterRef;
	//SDLRenderObject* chargebarShellRef;
};


#endif